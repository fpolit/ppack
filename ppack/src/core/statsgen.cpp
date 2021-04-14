// statgen stats struct (property , occurence)
typedef struct statstruct
{
  unsigned long total=0; //total number of analyzed passwords
  map<SCS, int> scs;
  map<Mask, int> mask;
  map<unsigned int, int> length;
}statstruct;
