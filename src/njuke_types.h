#ifndef NJUKE_TYPES_H
#define NJUKE_TYPES_H


/* In an effort to get better aquinted with the types used by Linux
 * we use a list type similar to the one in include/linux/list.h.
 *
 * Insted of having a list of nodes pointing to the data, the data
 * contains a struct njuke_list_head that is the actual list nodes.
 */

struct njuke_list_head {
        struct njuke_list_head *next;
        struct njuke_list_head *prev;
};

/* The parameters used in the list macros:
 * ptr - Pointer to a struct njuke_list_head.
 * type - The type of the containing stucture.
 */
#define NJUKE_LIST_ENTRY(ptr, type, member) \
        (type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member))

#define NJUKE_LIST_FIRST_ENTRY(ptr, type, member) \
        NJUKE_LIST_ENTRY((ptr)->next, type, member)

#define NJUKE_LIST_NEXT_ENTRY(pos, member) \
        NJUKE_LIST_ENTRY((pos)->member.next, typeof(*(pos)), member)

#define NJUKE_LIST_FOR_EACH(pos, head) \
        for (index = head->next; index != head; index = index->next)

#define NJUKE_LIST_FOR_EACH_ENTRY(pos, head, member)                   \
        for (pos = NJUKE_LIST_FIRST_ENTRY(head, typeof(*pos), member); \
             &pos->member != (head);                                   \
             pos = NJUKE_LIST_NEXT_ENTRY(pos, member))


static inline void njuke_list_init(struct njuke_list_head *list)
{
        list->next = list;
        list->prev = list;
}

static inline int njuke_list_empty(struct njuke_list_head *head)
{
        return head->next == head;
}

static inline void njuke_list_add(struct njuke_list_head *new,
                                  struct njuke_list_head *head)
{
        new->next = head;
        new->prev = head->prev;
        head->prev->next = new;
        head->prev = new;
}

static inline void njuke_list_del(struct njuke_list_head *entry)
{
        entry->prev->next = entry->next;
        entry->next->prev = entry->prev;
}

struct njuke_song {
        struct njuke_list_head _list;
        unsigned long id;
        unsigned long votes;
        char *name;
        char *artist;
};

struct njuke_event {
        struct njuke_list_head _list;
        unsigned long id;
        char *name;
        struct njuke_list_head songs;
};

struct njuke_event *njuke_event_create(const char *name);

void njuke_event_free(struct njuke_event *event);

void njuke_event_clear(struct njuke_event *event);

void njuke_event_print(const struct njuke_event *event);

struct njuke_song *njuke_song_create(const char *name, const char *artist);

void njuke_song_free(struct njuke_song *song);

void njuke_song_print(const struct njuke_song *song);

#endif
