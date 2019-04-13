//
//  virt_mem.c
//  virt_mem
//
//  Created by William McCarthy on 3/23/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define ARGC_ERROR 1
#define FILE_ERROR 2
#define BUFLEN 256
#define FRAME_SIZE  256


//-------------------------------------------------------------------
unsigned int getpage(size_t x) { return (0xff00 & x) >> 8; }
unsigned int getoffset(unsigned int x) { return (0xff & x); }

void getpage_offset(unsigned int x) {
  unsigned int page = getpage(x);
  unsigned int offset = getoffset(x);
  printf("x is: %u, page: %u, offset: %u, address: %u, paddress: %u\n", x, page, offset,
         (page << 8) | getoffset(x), page * 256 + offset);
}

int main(int argc, const char * argv[]) {
  FILE* fadd = fopen("addresses.txt", "r");
  if (fadd == NULL) { fprintf(stderr, "Could not open file: 'addresses.txt'\n");  exit(FILE_ERROR);  }

  FILE* fcorr = fopen("correct.txt", "r");
  if (fcorr == NULL) { fprintf(stderr, "Could not open file: 'correct.txt'\n");  exit(FILE_ERROR);  }

  FILE * fbin =fopen("BACKING_STORE.bin","r");
  if(fbin==NULL){fprintf(stderr,"Could not open file BACKING_STORE.bin"); exit(FILE_ERROR);}

  char buf[BUFLEN];
  int pageTable[FRAME_SIZE];
  
  char phys_mem[FRAME_SIZE];

  unsigned int page, offset, physical_add, frame = 0;
  unsigned int logic_add;                   // read from file address.txt
  unsigned int virt_add, phys_add, value;  // read from file correct.txt
  int pagefault=0;
  int tlbHit =0;
 //  phys_add = frame[0]+ offset;

      // not quite correct -- should search page table before creating a new entry
      //   e.g., address # 25 from addresses.txt will fail the assertion
      // TODO:  add page table code
    
     // virt_add=page+offset;
      //phys_add=frame+offset;

     // address split it page + offset 
     // go to page table write into pagetable
     //read next frame and put into physcial memory
     //construct physical addre frame+offset then print out value and compare to correct.txt
     // if its already there dont need to do anything but get address and read in value
     
   // phys_mem[FRAME_SIZE][buf]
   int l=0;
   while(l<FRAME_SIZE)
   {
      fscanf(fadd, "%d", &logic_add); 
      page=getpage(logic_add);
      offset = getoffset(logic_add);
      for(int i=0; i<FRAME_SIZE;++i)
      {
        pageTable[i]=page;
        frame=pageTable[i];
        phys_add=frame+offset;
        phys_mem[i]= phys_add;
        
        if (page !=pageTable[i])  //  page fault-not found in page table then go to backing store-bin
        {
          pagefault++;
        } 
      } 
   }
 
      // TODO:  add TLB code

      for(int i=0; i<BUFLEN;i++)
      {
        if(page==buf[i])   // tlbhit 
        {
          frame=buf[i];
          tlbHit++;
        }   //if miss go to page table
        
      }
      phys_add = frame+offset;

  while (frame < 20) 
  {
    
    fscanf(fcorr, "%s %s %d %s %s %d %s %d", buf, buf, &virt_add,
           buf, buf, &phys_add, buf, &value);  // read from file correct.txt

    fscanf(fadd, "%d", &logic_add);  // read from file address.txt
    page = getpage(logic_add);
    offset = getoffset(logic_add);
    
    physical_add = frame++ * FRAME_SIZE + offset;
    
    assert(physical_add == phys_add);
    // todo: read BINARY_STORE and confirm value matches read value from correct.txt
      
        fopen("BACKING_STORE.bin","r");
         fscanf(fbin,"%d",&value);
          fseek(fcorr,value,SEEK_SET);
          fread(buf,value,BUFLEN,fcorr);
          for(int i=0;i<BUFLEN;i++)
          {


           if(buf[i] == page)
           {
             value=buf[i];

           }
          }
          

    printf("logical: %5u (page:%3u, offset:%3u) ---> physical: %5u -- passed\n", logic_add, page, offset, physical_add);
    if (frame % 5 == 0) { printf("\n"); }
  }
  fclose(fcorr);
  fclose(fadd);
  
  printf("ALL logical ---> physical assertions PASSED!\n");
  printf("!!! This doesn't work passed entry 24 in correct.txt, because of a duplicate page table entry\n");
  printf("--- you have to implement the PTE and TLB part of this code\n");
  printf("Page fault rate %d\n",pagefault);
  printf("TLB hit rate %d\n",tlbHit);
  printf("\n\t\t...done.\n");
  return 0;
}
