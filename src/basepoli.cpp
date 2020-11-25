
Base::Base(poliStruct init)
{
  bstruct = init;
  string init_mask;

  init_mask = repeat("?l", bstruct.minlower) +\
    repeat("?d", bstruct.minupper) +\
    repeat("?u", bstruct.minupper) +\
    repeat("?s", bstruct.minspecial);

  Mask initMask(init_mask);

  base = new vector<Mask>;
  base->push_back(initMask);
  length = 1;
}

Base::~Base()
{
  delete [] base;
}

void Base::appendMask(Mask step)
{
  base->push_back(step);
}

void Base::maskStep()
{
  vector<Mask> *step_base = new vector<Mask>;
  for(Mask mask : *base)
    {
      maskStruct mstruct = maskAnalysis(mask);

      if(mstruct.lowercase <= bstruct.maxlower)
        {
          step_base->push_back(mask + "?l");
          if(mstruct.digit <= bstruct.maxdigit)
              step_base->push_back(mask + "?d");

          if(mstruct.uppercase <= bstruct.maxupper)
              step_base->push_back(mask + "?u");

          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.digit <= bstruct.maxdigit)
        {
          step_base->push_back(mask + "?d");
          if(mstruct.uppercase <= bstruct.maxupper)
              step_base->push_back(mask + "u");
          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.uppercase <= bstruct.maxupper)
        {
          step_base->push_back(mask + "?u");
          if(mstruct.special <= bstruct.maxspecial)
            step_base->push_back(mask + "?s");
        }
      else if(mstruct.special <= bstruct.maxspecial)
        {
          step_base->push_back(mask + "?s");
        }
    }

  // replace the updated base(step_base) with base
  delete [] base; // fre memory of base = vector<Mask>
  base = step_base;
  step_base = nullptr;
  length += 1;
}
