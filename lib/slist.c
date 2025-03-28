#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char * data;
    struct Node * next;
} Node;

typedef struct {
    size_t size;
    size_t item_size;
    Node * head;
} Slist;

void * slist_create(size_t itemSize) {
    if (itemSize == 0) return NULL;
    Slist * slist = malloc(sizeof(Slist));
    if (NULL == slist) return NULL;
    slist->item_size = itemSize;
    slist->size = 0;
    slist->head=NULL;
    return slist;
}

static Node * create_node(const Slist * slist) {
    Node * new = malloc(sizeof(Node));
    if (new == NULL) return NULL;
    new->data = malloc(((Slist *)slist)->item_size);
    new->next = NULL;                                 // fixed
    if (new->data == NULL) {
        free(new);
        return NULL;
    }
    ((Slist *)slist)->size += 1;
    return new;
}

static Node * delete_node(const Slist * slist, Node * node, void(*destroy)( void * )) { // возвращает следующий узел
    if (node == NULL) return NULL;
    Node * next = node->next;
    if (destroy != NULL) destroy(node->data);
    free(node->data);
    free(node);
    ((Slist *)slist)->size -= 1;
    return next;
}

void slist_destroy(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    slist_clear(slist, destroy);                       // fixed
    free(slist);
}

void slist_clear(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Node* current = ((Slist *)slist)->head;
    while (current != NULL) {
        current = delete_node(slist, current, destroy);
    }
    ((Slist *)slist)->head = NULL;
    ((Slist *)slist)->size = 0;
}

void * slist_init(void * slist, size_t itemSize, void(*destroy)(void*)) {
    if (itemSize == 0 || slist == NULL) return NULL;
    slist_clear((Slist *)slist, destroy);
    ((Slist *)slist)->item_size = itemSize;
    ((Slist *)slist)->size = 0;
    return slist;
}

size_t slist_count(const void * slist) {
    if (slist == NULL) return INVALID;
    return ((Slist *)slist)->size;
}

void * slist_item(void * slist, size_t i) {
    if (slist == NULL || i >= slist_count(slist)) return NULL;    // fixed
    Node * node = ((Slist *)slist)->head;
    while (node != NULL && i > 0) {                            // fixed
        node = node->next;
        i--;
    }
    return node == NULL ? NULL : node->data;
}

void * slist_prepend(void * slist) {
    if (slist == NULL) return NULL;
    Node * node = create_node(slist);
    if (node == NULL) return NULL;
    node->next = ((Slist *)slist)->head;
    ((Slist *)slist)->head = node;
    return node->data;
}

void slist_remove(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;                                   // fixed
    ((Slist *)slist)->head = delete_node(slist, ((Slist *)slist)->head, destroy);
}

size_t slist_first(const void * slist) {
    if (slist == NULL || ((Slist *)slist)->head == NULL) return slist_stop(slist);
    return (size_t)((Slist *)slist)->head; // приведение указателя к целому числу
}

size_t slist_next(const void * slist, size_t item_id) {
    if (slist == NULL ||  item_id == slist_stop(slist)) return slist_stop(slist);   // fixed
    Node * node = (Node *)item_id;
    return (size_t)node->next;  // приведение целого числа к указателю
}

size_t slist_stop(const void * slist) {
    return (size_t)NULL;
}

void * slist_current(const void * slist, size_t item_id) {
    if (slist == NULL || item_id == slist_stop(slist)) return NULL;
    return ((Node *)item_id)->data;
}

void * slist_insert(void * slist, size_t item_id) {
    if (slist == NULL ) return NULL; // fixed
    if (item_id == slist_stop(slist)) {
        if (slist_count(slist) != 0) return NULL;
        return slist_prepend(slist);
    }
    Node* current = (Node *)item_id;
    Node* new = create_node(slist);
    if (new == NULL) return NULL;
    new->next = current->next;
    current->next = new;
    return new->data;
}

void slist_erase(void * slist, size_t item_id, void(*destroy)( void * )) {
    if (slist == NULL || slist_stop(slist) == item_id) return;
    Node* current = ((Slist *)slist)->head;
    if (current == (Node *)item_id) {
        slist_remove(slist, destroy);
        return;
    }
    while ((size_t)(current->next) != item_id) {
        if (current == NULL) return;
        current = current->next;
    }
    current->next = delete_node(slist, current->next, destroy);
}