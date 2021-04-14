/*
 * Password class implementarion
 * Password class reimplemented 23 nov 20202
 *
 *
 * Password class with omp support - 30 nov 2020*
 *
 * Depuration:
 * Passowrd class tested 24 nov 2020.
 *
 *
 * No tested functions:
 *
 *
 *
 * No implemented functions:
 * vector<Mask> Mask::permutations();
 *
 * Warning:
 *
 * SOLVED - 24 nov 2020
 * ---- functions isSOMTHING problems <> 24 nov 2020 ----
 * isSOMETHING(work of with string of length 1) but function PERMIT string of length greater than 1,
 * in such case implement a loop over all the letther in that word and return true
 * if all the letthers are of SOMETHING type.
 *
 * Functions with OMP support:
 * static bool isdigit(string word);
 * static bool islower(string word);
 * static bool isupper(string word);
 * static bool isspecial(string word);
 *
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


// tested - 24 nov 2020
Password::Password(string passwd)
  :string(passwd), mask("")
{
  mask = analyzePassword(passwd);
}

// check functions
bool Password::check_length(Password passwd, int minlength, int maxlength)
/*
 * maxlength = -1, means that the maximum length of password is infinite.
 */
{
  int passwd_length = passwd.size();
  if(maxlength != -1)
    {
      if(passwd_length >= minlength && passwd_length <= maxlength)
        return true;
    }
  else
    {
      if(passwd_length >= minlength)
        return true;
    }

  return false;
}

// check if a password have a SCS type in pscs(posibles SCS)
bool Password::check_scs(Password passwd, vector<SCS> pscs)
{
  if(std::find(pscs.begin(), pscs.end(), passwd.getSCS()) == pscs.end())
    return false;
  return true;
}

// check if a password have a ACS type in pscs(posibles ACS)
bool Password::check_acs(Password passwd, vector<ACS> pacs)
{
  if(std::find(pacs.begin(), pacs.end(), passwd.getACS()) == pacs.end())
    return false;
  return true;
}

// Tested with omp support - 30 nov 2020
bool Password::isdigit(string word)
/*
 * verify if a word id only of digits or if a letther(word of one character) is a digit
 */
{
  bool isdigitMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!isdigitMaster) continue;

      if (charset::digits.find(word[k]) == string::npos)
        isdigitMaster =  false;
    }

  return isdigitMaster;
}


// Tested with omp support - 30 nov 2020
bool Password::islower(string word)
/*
 * verify if a word is only lowercase or if a letther(word of one character) is a lowercase
 */
{
  bool islowerMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!islowerMaster) continue;

      if (charset::ascii_lowercase.find(word[k]) == string::npos)
        islowerMaster =  false;
    }

  return islowerMaster;
}


// Tested with omp support - 30 nov 2020
bool Password::isupper(string word)
/*
 * verify if a word is only uppercase characters or
 * if a letther(word of one character) is a uppercase character
 */
{
  bool isupperMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!isupperMaster) continue;

      if (charset::ascii_uppercase.find(word[k]) == string::npos)
        isupperMaster =  false;
    }

  return isupperMaster;
}


// Tested with omp support - 30 nov 2020
bool Password::isspecial(string word)
/*
 * verify if a word is only of special characters or
 * if a letther(word of one character) is a special character
 */
{

  bool isspecialMaster = true;
#pragma omp parallel for shared(word)
  for(int k=0; k<word.size(); k++)
    {
      if(!isspecialMaster) continue;

      if (charset::special.find(word[k]) == string::npos)
        isspecialMaster =  false;
    }

  return isspecialMaster;
}

// tested - 24 nov 2020
Mask Password::analyze_password(string passwd)
/*
 * Analize a string and create a Mask object,
 * also parse the Simple Charset of the password and
 * finally return it.
 */
{
    Mask mask_parser;
    // compute the mask of the password and fill the maskStruct
    // #pragma omp parallel for ordered
    //     shared(master_mask, passwd, symbols, passwdStruct)
    for(auto letther: passwd)
    {
      if(Password::islower(letther))
        mask_parser.realloc("?l");
      else if(Password::isupper(letther))
        mask_parser.realloc("?u");
      else if(Password::isdigit(letther))
        mask_parser.realloc("?d");
      else //the character is a special character
        mask_parser.realloc("?s");
    }

    maskStruct mstruct = mask_parser.get_mask_struct();
    // scsParser is defined in mask.hpp and implemented in mask.cpp
    // and password.cpp is importing mask.hpp
    mask_parser.set_scs(Mask::scs_parser(mstruct));

    return mask_parser;

}
