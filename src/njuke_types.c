#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "njuke_types.h"


/* Event */
struct njuke_event *njuke_event_create(const char *name)
{
        struct njuke_event *event;

        event = malloc(sizeof(*event));
        event->name = strdup(name);
        njuke_list_init(&event->songs);
        return event;
}

void njuke_event_free(struct njuke_event *event)
{
        njuke_event_clear(event);
        free(event->name);
        free(event);
}

void njuke_event_clear(struct njuke_event *event)
{
        while (!njuke_list_empty(&event->songs)) {
                struct njuke_list_head *head;

                head = event->songs.next;
                njuke_list_del(head);
                free(NJUKE_LIST_ENTRY(head, struct njuke_event, _list));
        }
}

void njuke_event_print(const struct njuke_event *event)
{
        struct njuke_song *song;

        NJUKE_LIST_FOR_EACH_ENTRY(song, &event->songs, _list)
                njuke_song_print(song);
}

/* Song */
struct njuke_song *njuke_song_create(const char *name, const char *artist)
{
        struct njuke_song *song;

        song = malloc(sizeof(*song));
        song->name = strdup(name);
        song->artist = strdup(artist);
        song->votes = 0;
        njuke_list_init(&song->_list);
        return song;
}

void njuke_song_free(struct njuke_song *song)
{
        free(song->name);
        free(song->artist);
        free(song);
}

void njuke_song_print(const struct njuke_song *song)
{
        printf("%s - %s    %lu\n", song->artist, song->name, song->votes);
}
