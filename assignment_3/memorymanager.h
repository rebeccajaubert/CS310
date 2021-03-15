#ifndef MEMORY_MANAGER_H_INCLUDE
#define MEMORY_MANAGER_H_INCLUDE

struct FILE;
struct PCB;

int countTotalPages(FILE *f);
void loadPage(int pageNumber, FILE *f, int frameNumber);
int findFrame();
int findVictim(struct PCB* p);
int updateFrame(int frameNumber, int victimFrame, FILE* page);
int updatePageTable(struct PCB *p, int pageNumber, int frameNumber, int victimFrame);
int launcher(FILE* p);

#endif 
