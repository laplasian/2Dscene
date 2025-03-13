#include "new.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

// Реализация функции new
void *new(const void *_class, ...)
{

    const struct Class *class = _class;

    void *p = calloc(1, class->size);
    assert(p);

    // Прописывание класса объекта. Все объекты в системе устроены так, что в самых
    // первых байтах памяти, выделенной под объект, содержится указатель на
    // глобальную структуру типа Class, описывающую класс этого объекта. Здесь
    // этот указатель лежит в переменной class. p как раз указывает на то место,
    // куда должен лечь class.
    *(const struct Class **)p = class;

    // Если задан конструктор...
    if (class->ctor) {
        va_list ap;

        // Инициализируем работу с переменными аргументами. После выполнения
        // va_start ap будет указывать на следующий аргумент после _class,
        // то есть первый аргумент, который должен достаться функции-конструктору.
        va_start(ap, _class);

        // Вызываем конструктор
        p = class->ctor(p, &ap);


        // Очищаем ap
        va_end(ap);
    }

    // Возвращаем указатель на объект
    return p;
}

// Реализация функции delete
void delete(void *self)
{
    // Поскольку нам потребуется доступ к описанию класса объекта,
    // сделаем удобное преобразование типов
    const struct Class **cp = self;

    // Проверка деструктора. *cp получает указатель на struct Class,
    // из которой достаём поле dtor
    if (self && *cp && (*cp)->dtor)
        // Если деструктор задан, вызываем его. Он должен вернуть указатель
        // на исходный блок памяти
        self = (*cp)->dtor(self);

    // Освобождаем выделенный блок памяти
    free(self);
}

// Реализация функции draw
void draw(const void *self)
{
    // Поскольку нам потребуется доступ к описанию класса объекта,
    // сделаем удобное преобразование типов
    const struct Class * const *cp = self;

    // Проверяем, что объект, описание класса и указатель на реализацию виртуального
    // метода являются ненулевыми
    assert(self && *cp && (*cp)->draw);

    // Вызываем виртуальный метод по указателю
    (*cp)->draw(self);
}