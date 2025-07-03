#include "json_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

JObject *parse_json(const char *filename) {
  json_error_t error;
  json_t *root = json_load_file(filename, 0, &error);
  if (!root) {
    fprintf(stderr, "Fehler beim Laden der Datei: %s\n", error.text);
    return NULL;
  }

  JObject *head = NULL;
  JObject *last = NULL;

  size_t index;
  json_t *value;

  json_array_foreach(root, index, value) {
    json_t *jname = json_object_get(value, "name");
    json_t *jage = json_object_get(value, "age");

    JObject *node = malloc(sizeof(JObject));
    if (!node) {
      perror("malloc");
      break;
    }

    node->name = strdup(json_string_value(jname));
    node->age = (int)json_integer_value(jage);
    node->next = NULL;

    if (!head) {
      head = node;
      last = node;
    } else {
      last->next = node;
      last = node;
    }
  }

  json_decref(root);
  return head;
}

void print_list(JObject *head) {
  for (JObject *p = head; p != NULL; p = p->next) {
    printf("Name: %s, Alter: %d\n", p->name, p->age);
  }
}

void free_list(JObject *head) {
  while (head) {
    JObject *temp = head;
    head = head->next;
    free(temp->name);
    free(temp);
  }
}
