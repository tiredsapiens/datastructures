#include "hashtables.h"
#include "string.h"
#include <stdio.h>
char *words[70] = {
    "apple",        "banana",       "cherry",      "date",
    "elderberry",   "fig",          "grape",       "honeydew",
    "kiwi",         "lemon",        "mango",       "nectarine",
    "orange",       "papaya",       "quince",      "raspberry",
    "strawberry",   "tangerine",    "watermelon",  "apricot",
    "blackberry",   "cantaloupe",   "dragonfruit", "kiwifruit",
    "lime",         "melon",        "nectar",      "peach",
    "pear",         "plum",         "pomegranate", "pineapple",
    "papaya",       "passionfruit", "persimmon",   "starfruit",
    "tamarind",     "mandarin",     "grapefruit",  "blueberry",
    "coconut",      "custardapple", "carambola",   "soursop",
    "sugarapple",   "tangerine",    "tomato",      "zucchini",
    "kumquat",      "dragonfruit",  "loquat",      "guava",
    "jambolan",     "lychee",       "mangosteen",  "salak",
    "longan",       "rambutan",     "marula",      "soursop",
    "miraclefruit", "yellowmombin", "calamondin",  "buddha'shand",
    "chayote",      "roseapple",    "jackfruit",   "breadfruit",
    "sapodilla",    "durian",
};
int main() {

  hashtable *h_table = create_hashtable();
  for (int i = 0; i < 70; i++) {
    char *word = words[i];
    void *result = get_value_by_key(h_table, word);
    if (result == NULL) {
      int count = 1;
      hashtable_add_entry(h_table, word, (void *)&count, sizeof(int));
    } else {

      (*((int *)result))++;
    }
  }
  void *res = get_value_by_key(h_table, "banana");
  if (res == NULL) {
    printf("SOMETHING WENT WRONG\n");
    return 1;
  }
  printf(" number of %d\n", *(int *)res);

  // char **all_keys = get_all_keys(h_table);
  // for (int i = 0; i < h_table->count; i++) {
  //   printf("%s :%d\n", all_keys[i],
  //          *(int *)get_value_by_key(h_table, all_keys[i]));
  // }
  void **valuess = get_all_values(h_table);

  for (int i = 0; i < h_table->count; i++) {
    printf("%d\n", *((int **)valuess)[i]);
  }
}
