#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class StringValidator
{
public:
  virtual ~StringValidator() {}

  virtual bool isValid(string input) = 0;
};
class MinLengthValidator : public StringValidator
{
public:
  MinLengthValidator(size_t min_length)
      : min_length(min_length) {}

  bool isValid(string input) override
  {
    return input.length() >= min_length;
  }

private:
  size_t min_length;
};

class MaxLengthValidator : public StringValidator
{
public:
  MaxLengthValidator(size_t max_length)
      : max_length(max_length) {}

  bool isValid(string input) override
  {
    return input.length() <= max_length;
  }

private:
  size_t max_length;
};

class PatternValidator : public StringValidator
{
public:
  PatternValidator(std::string pattern) : pattern(pattern) {}
  virtual bool isValid(std::string input);

private:
  std::string pattern;
  bool chars_match(int pattern_char, int text_char);
  size_t find_match(std::string const &input);
};

bool PatternValidator::chars_match(int pattern_char, int text_char)
{
  if (pattern_char == 'D')
  {
    return isdigit(text_char);
  }
  if (pattern_char == 'A')
  {
    return isalpha(text_char);
  }
  if (pattern_char == '?')
  {
    return true;
  }

  if (islower(pattern_char))
  {
    return pattern_char == tolower(text_char);
  }
  if (ispunct(pattern_char))
  {
    return pattern_char == text_char;
  }
  return false;
}

size_t PatternValidator::find_match(std::string const &text)
{
  size_t match_pos = std::string::npos;

  size_t len_pattern = pattern.length();
  if (len_pattern == 0)
  {
    return match_pos;
  }

  for (size_t idx_text = 0;
       match_pos == std::string::npos && idx_text + len_pattern <= text.length();
       idx_text++)
  {
    bool all_match = true;
    for (size_t idx_pattern = 0; all_match && idx_pattern < len_pattern; idx_pattern++)
    {
      all_match = chars_match(pattern[idx_pattern], text[idx_text + idx_pattern]);
    }
    if (all_match)
    {
      match_pos = idx_text;
    }
  }

  return match_pos;
}

bool PatternValidator::isValid(std::string input)
{
  return find_match(input) != std::string::npos;
}

void printValid(StringValidator &validator, string input)
{
  cout << "The string '" << input << "' is "
       << (validator.isValid(input) ? "Valid" : "Invalid")
       << endl;
}

int main()
{
  cout << "MinLengthValidator" << endl;

  MinLengthValidator min(6);

  printValid(min, "hello");
  printValid(min, "welcome");

  cout << endl;

  cout << "MaxLengthValidator" << endl;

  MaxLengthValidator max(6);

  printValid(max, "hello");
  printValid(max, "welcome");

  cout << endl;

  cout << "PatternValidator" << endl;

  PatternValidator pattern("welcome");

  printValid(pattern, "hello welcome");
  printValid(pattern, "hello");

  cout << endl;

  return 0;
}

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

class StringValidator
{
public:
    virtual ~StringValidator() {};
    virtual bool isValid(string input) = 0;
};

class MinLengthValidator : public StringValidator
{
public:
    MinLengthValidator(size_t min_length)
        : min_length(min_length)
    {
    }

    bool isValid(string input) override
    {
        return input.length() >= min_length;
    }

private:
    size_t min_length;
};

class MaxLengthValidator : public StringValidator
{
public:
    MaxLengthValidator(size_t max_length)
        : max_length(max_length)
    {
    }

    bool isValid(string input) override
    {
        return input.length() <= max_length;
    }

private:
    size_t max_length;
};

class LengthValidator : public StringValidator
{
public:
    LengthValidator(int min, int max)
        : min_validator(min), max_validator(max)
    {
    }

    bool isValid(string input) override
    {
        return min_validator.isValid(input) &&
               max_validator.isValid(input);
    }

private:
    MinLengthValidator min_validator;
    MaxLengthValidator max_validator;
};

class UpAlphaValidator : public StringValidator
{
public:
    bool isValid(string input) override
    {
        for (char c : input)
        {
            if (isupper(c))
            {
                return true;
            }
        }

        return false;
    }
};

class LowAlphaValidator : public StringValidator
{
public:
    bool isValid(string input) override
    {
        for (char c : input)
        {
            if (islower(c))
            {
                return true;
            }
        }

        return false;
    }
};

class DigitValidator : public StringValidator
{
public:
    bool isValid(string input) override
    {
        for (char c : input)
        {
            if (isdigit(c))
            {
                return true;
            }
        }

        return false;
    }
};

class SpecialCharValidator : public StringValidator
{
    string specialChars = "!@#$%^&*()_+{}|:<>?`-=[]\\;',./";

public:
    bool isValid(string input) override
    {
        for (char c : input)
        {
            if (specialChars.find(c) != string::npos)
            {
                return true;
            }
        }

        return false;
    }
};

class PasswordValidator : public StringValidator
{
public:
    PasswordValidator()
        : length_validator(8, 8)
    {
    }

    bool isValid(string input) override
    {
        return length_validator.isValid(input) &&
               up_validator.isValid(input) &&
               low_validator.isValid(input) &&
               digit_validator.isValid(input) &&
               special_validator.isValid(input);
    }

private:
    LengthValidator length_validator;
    UpAlphaValidator up_validator;
    LowAlphaValidator low_validator;
    DigitValidator digit_validator;
    SpecialCharValidator special_validator;
};

void printValid(StringValidator &validator, string input)
{
    cout << "The string '" << input << "' is "
         << (validator.isValid(input) ? "valid" : "invalid");
}

int main()
{
    PasswordValidator validator;

    printValid(validator, "abc123!x");
}