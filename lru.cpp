#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

struct Page
{
    int pageNumber;
    int counter;
};

int findLRUIndex(struct Page frames[], int n)
{
    int minIndex = 0;
    for (int i = 1; i < n; i++)
    {
        if (frames[i].counter < frames[minIndex].counter)
        {
            minIndex = i;
        }
    }
    return minIndex;
}

void pageReplacementLRU(int pageRequests[], int numRequests, int numFrames)
{
    struct Page frames[numFrames];

    for (int i = 0; i < numFrames; i++)
    {
        frames[i].pageNumber = -1;
        frames[i].counter = 0;
    }

    int pageFaults = 0;

    for (int i = 0; i < numRequests; i++)
    {
        bool pageFound = false;

        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j].pageNumber == pageRequests[i])
            {
                frames[j].counter = i; // Update counter for the found page
                pageFound = true;
                break;
            }
        }

        if (!pageFound)
        {
            int lruIndex = findLRUIndex(frames, numFrames);
            frames[lruIndex].pageNumber = pageRequests[i];
            frames[lruIndex].counter = i;
            pageFaults++;
        }

        printf("Page %d: [", pageRequests[i]);
        for (int j = 0; j < numFrames; j++)
        {
            printf("%d ", frames[j].pageNumber);
        }
        printf("] Page Faults: %d\n", pageFaults);
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main()
{
    int pageRequests[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int numRequests = sizeof(pageRequests) / sizeof(pageRequests[0]);
    int numFrames = 3;

    printf("LRU Page Replacement:\n");
    pageReplacementLRU(pageRequests, numRequests, numFrames);

    return 0;
}
