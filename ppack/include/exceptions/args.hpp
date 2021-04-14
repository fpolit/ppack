/*
 * args exceptions
 *
 * Maintainer: glozanoa <glozanoa@uni.pe>
 */


class Exception : public std::exception
{
private:
  string warning;

public:
  Exception(string warningMsg)
  {
    warning = warningMsg;
  }
  const char* what() const throw()
  {
    return warning.c_str();
  }
};
