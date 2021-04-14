#include "../../include/core/policygen.hpp"

// compute a set of bases[PoliBase]
// (with length equal to minlength  till maxlength)
// tested 27 nov 2020
// REWRITE (NOT ALL) THIS FUNCTION  - date Apr 14  2021
void corePolicygen(pstruct pargs)
{
  Base *base = new Base(pargs);
  int minlength = base->getMinLength();
  int baseLength = base->getLength();
  while(baseLength < minlength)
    {
      base = maskStep(base); //increase the length of base in one
      baseLength += 1;
    }


  // now the length of base is equal to minlength-1(policygen paramemter)
  //vector<Base*>* basePoli = new vector<Base*>;
  if(pargs.show)
  {
    ofstream* outputPolicygen = new ofstream;
    outputPolicygen->open(pargs.output);
    try {
#pragma omp parallel for shared(base, outputPolicygen) ordered
      for(int step=base->getLength(); step < base->getMaxLength(); step++)
      {
        #pragma omp ordered
        base->showMasks(pargs.pretty);
        writeMasks(base, outputPolicygen);
        base = maskStep(base);
      }
      base->showMasks(pargs.pretty);
      writeMasks(base, outputPolicygen);
      outputPolicygen->close();

      if(pargs.pretty)
        FinePrint::successful("Generated masks have written in [" + pargs.output + "]");
      else
       cout << "Generated masks have written in [" + pargs.output + "]" << endl;

    } catch (std::exception& error) {
      cout << error.what() << endl;
      outputPolicygen->close();
    }
  }
  else
  {

    ofstream* outputPolicygen = new ofstream;
    outputPolicygen->open(pargs.output);
    try {
      for(int step=base->getLength(); step < base->getMaxLength(); step++)
      {
        writeMasks(base, outputPolicygen);
        base = maskStep(base);
      }
      writeMasks(base, outputPolicygen);
      outputPolicygen->close();

      if(pargs.pretty)
        FinePrint::successful("Generated masks have written in [" + pargs.output + "]");
      else
       cout << "Generated masks have written in [" + pargs.output + "]" << endl;
    } catch (std::exception& error) {
      cout << error.what() << endl;
      outputPolicygen->close();
    }
  }
  delete base;
}
