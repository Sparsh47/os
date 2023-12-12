#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 3

struct Page
{
    int pageNumber;
};

void pageReplacementFIFO(int pageRequests[], int numRequests, int numFrames)
{
    struct Page frames[numFrames];

    for (int i = 0; i < numFrames; i++)
    {
        frames[i].pageNumber = -1;
    }

    int pageFaults = 0;
    int nextFrame = 0;

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
            frames[nextFrame].pageNumber = pageRequests[i];
            nextFrame = (nextFrame + 1) % numFrames;
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

    printf("FIFO Page Replacement:\n");
    pageReplacementFIFO(pageRequests, numRequests, numFrames);

    return 0;
}
