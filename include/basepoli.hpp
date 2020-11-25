
// base class of policygen
class Base
{
private:
  poliStruct bstruct; // base struct , entered options for policygen
  vector<Mask> *base;
  unsigned int length;

public:

  Base(poliStruct init);
  void maskStep(); // generate all the posible mask of length = length +1(step)

  void appendMask(Mask step); // next step mask

  unsigned int getLength(){return length;}
  int numberMasks(){return base->size();}


  int getPoliMinLength(){return bstruct.minlength;}
  int getPoliMaxLength(){return bstruct.maxlength;}

  ~Base();
};
