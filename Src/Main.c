#include <Hallocy/Allocator.h>

int main() {
    void *test = hallocy_malloc(10);
    hallocy_free(test);
    return 0;
}