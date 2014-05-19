# Memory
## Virtual Memmory
* A virtual memory is **page number** + **byte offset** in a page
* Low order **n* bits are the byte offset
* Remaining high order bits are the page number
![virtual addr](http://i.imgur.com/6gQdZYJ.png?1)

## Role of the page table
* Virtual memory givev processes the impression of long contiguius memeory
* In reality, the memeory of a process is dispersed throughout the physical memory
  or disk (swap)
