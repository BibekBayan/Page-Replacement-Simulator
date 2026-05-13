#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isHit(int frames[], int size, int page) {
    for (int i = 0; i < size; i++) {
        if (frames[i] == page)
            return 1;
    }
    return 0;
}

int fifo(int frame_count, int pages[], int n) {
    int frames[frame_count];
    int front = 0, faults = 0;

    for (int i = 0; i < frame_count; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (!isHit(frames, frame_count, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % frame_count;
            faults++;
        }
    }
    return faults;
}

int lru(int frame_count, int pages[], int n) {
    int frames[frame_count], time[frame_count];
    int counter = 0, faults = 0;

    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
        time[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                counter++;
                time[j] = counter;
                found = 1;
                break;
            }
        }

        if (!found) {
            int min = 0;
            for (int j = 1; j < frame_count; j++) {
                if (time[j] < time[min])
                    min = j;
            }

            frames[min] = pages[i];
            counter++;
            time[min] = counter;
            faults++;
        }
    }
    return faults;
}

int optimal(int frame_count, int pages[], int n) {
    int frames[frame_count];
    int faults = 0;

    for (int i = 0; i < frame_count; i++)
        frames[i] = -1;

    for (int i = 0; i < n; i++) {
        if (isHit(frames, frame_count, pages[i]))
            continue;

        int pos = -1, farthest = i;

        for (int j = 0; j < frame_count; j++) {
            int k;
            for (k = i + 1; k < n; k++) {
                if (frames[j] == pages[k]) {
                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                    break;
                }
            }
            if (k == n) {
                pos = j;
                break;
            }
        }

        if (pos == -1)
            pos = 0;

        frames[pos] = pages[i];
        faults++;
    }
    return faults;
}

int lfu(int frame_count, int pages[], int n) {
    int frames[frame_count], freq[frame_count];
    int faults = 0;

    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
        freq[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int found = 0;

        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == pages[i]) {
                freq[j]++;
                found = 1;
                break;
            }
        }

        if (!found) {
            int min = 0;
            for (int j = 1; j < frame_count; j++) {
                if (freq[j] < freq[min])
                    min = j;
            }

            frames[min] = pages[i];
            freq[min] = 1;
            faults++;
        }
    }
    return faults;
}

int main(int argc, char *argv[]) {

    if (argc < 4) {
        printf("Usage: simulator <frames> <pages> <algo>\n");
        return 1;
    }

    int frame_count = atoi(argv[1]);
    char *pages_str = argv[2];
    char *algo = argv[3];

    int n = strlen(pages_str);
    int pages[n];

    for (int i = 0; i < n; i++)
        pages[i] = pages_str[i] - '0';

    printf("===== PAGE REPLACEMENT RESULT =====\n\n");
    printf("Frames: %d\nPages: %s\n\n", frame_count, pages_str);

    if (strcmp(algo, "COMPARE") == 0) {

        int f_fifo = fifo(frame_count, pages, n);
        int f_lru  = lru(frame_count, pages, n);
        int f_lfu  = lfu(frame_count, pages, n);
        int f_opt  = optimal(frame_count, pages, n);

        int total = n;

        printf("FIFO Faults: %d | Hit Ratio: %.2f\n", f_fifo, (float)(total - f_fifo) / total);
        printf("LRU Faults: %d | Hit Ratio: %.2f\n", f_lru, (float)(total - f_lru) / total);
        printf("LFU Faults: %d | Hit Ratio: %.2f\n", f_lfu, (float)(total - f_lfu) / total);
        printf("OPT Faults: %d | Hit Ratio: %.2f\n\n", f_opt, (float)(total - f_opt) / total);

        int min = f_fifo;
        char best[20] = "FIFO";

        if (f_lru < min) { min = f_lru; strcpy(best, "LRU"); }
        if (f_lfu < min) { min = f_lfu; strcpy(best, "LFU"); }
        if (f_opt < min) { min = f_opt; strcpy(best, "OPTIMAL"); }

        printf("Best Algorithm: %s\n", best);
    }
    else {
        printf("Use COMPARE mode\n");
    }

    return 0;
}