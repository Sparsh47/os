#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

struct Page
{
    int pageNumber;
    int nextReferenceIndex;
};

int findOptimalIndex(struct Page frames[], int numFrames, int pageRequests[], int numRequests, int currentIndex)
{
    int maxIndex = -1;
    int maxDistance = -1;

    for (int i = 0; i < numFrames; i++)
    {
        int distance = -1;

        for (int j = currentIndex; j < numRequests; j++)
        {
            if (frames[i].pageNumber == pageRequests[j])
            {
                distance = j;
                break;
            }
        }

        if (distance == -1)
        {
            return i; // If the page won't be referenced again, replace it
        }

        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxIndex = i;
        }
    }

    return maxIndex;
}

void pageReplacementOptimal(int pageRequests[], int numRequests, int numFrames)
{
    struct Page frames[numFrames];

    for (int i = 0; i < numFrames; i++)
    {
        frames[i].pageNumber = -1;
        frames[i].nextReferenceIndex = -1;
    }

    int pageFaults = 0;

    for (int i = 0; i < numRequests; i++)
    {
        bool pageFound = false;

        for (int j = 0; j < numFrames; j++)
        {
            if (frames[j].pageNumber == pageRequests[i])
            {
                pageFound = true;
                break;
            }
        }

        if (!pageFound)
        {
            int optimalIndex = findOptimalIndex(frames, numFrames, pageRequests, numRequests, i + 1);
            frames[optimalIndex].pageNumber = pageRequests[i];
            frames[optimalIndex].nextReferenceIndex = i;
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

    printf("Optimal Page Replacement:\n");
    pageReplacementOptimal(pageRequests, numRequests, numFrames);

    return 0;
}
