#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;

    for (i = 1; i < n; ++i) {
        if (time[i] < minimum) {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}

int main() {
    int frames, pages, i, j;
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("Enter number of pages: ");
    scanf("%d", &pages);

    int frame[frames], page[pages], counter[frames], time[frames];

    for (i = 0; i < frames; ++i) {
        frame[i] = -1; // Initialize frames to -1, indicating they are empty
        counter[i] = 0; // Initialize counter for each frame
        time[i] = 0;    // Initialize time for each frame
    }

    printf("Enter reference string:\n");

    for (i = 0; i < pages; ++i)
        scanf("%d", &page[i]);

    printf("\n");

    int pageFaults = 0, pageHits = 0;

    for (i = 0; i < pages; ++i) {
        int pageExists = 0;
        for (j = 0; j < frames; ++j) {
            if (frame[j] == page[i]) {
                pageExists = 1;
                counter[j]++;
                time[j] = i; // Update the time of the recently used page
                pageHits++;  // Increment hit count
                break;
            }
        }

        if (!pageExists) {
            int pos = findLRU(time, frames); // Find the position of the least recently used page
            frame[pos] = page[i];             // Replace the least recently used page with the current page
            counter[pos] = 1;                 // Reset the counter for the newly added page
            time[pos] = i;                    // Update the time of the recently used page
            pageFaults++;
        }

        printf("Frame Status after page %d: ", page[i]);
        for (j = 0; j < frames; ++j) {
            if (frame[j] == -1)
                printf("[ ] ");
            else
                printf("[%d] ", frame[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
    printf("Total Page Hits: %d\n", pageHits);

    float faultRatio = (float)pageFaults / pages * 100;
    float hitRatio = (float)pageHits / pages * 100;

    printf("Fault Ratio: %.2f%%\n", faultRatio);
    printf("Hit Ratio: %.2f%%\n", hitRatio);

    return 0;
}
