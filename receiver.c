#include "sit.h"

sit_receiver *
sit_receiver_new() {
  return calloc(1, sizeof(sit_receiver));
}