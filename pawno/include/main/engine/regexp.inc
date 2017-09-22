

stock bool:ContainsIP(const string[])
{
  new RegEx:rCIP;

  if( !rCIP ) rCIP = regex_build(".*[0-9]{1,3}[^0-9]{1,3}[0-9]{1,3}[^0-9]{1,3}[0-9]{1,3}[^0-9]{1,3}[0-9]{1,3}[^0-9]{1,7}[0-9]{3,5}.*");

  if(regex_match_exid(string, rCIP)) return true;
  else return false;
}

stock bool:IsValidEmail(const string[])
{
  new RegEx:rEMAIL;

  if( !rEMAIL ) rEMAIL = regex_build("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}$");

  if(regex_match_exid(string, rEMAIL)) return true;
  else return false;
}

stock bool:IsNumeric(const string[])
{
  new RegEx:rNUMER;

  if( !rNUMER ) rNUMER = regex_build("^[0-9]+$");

  if(regex_match_exid(string, rNUMER)) return true;
  else return false;
}

stock bool:IsPasswordCorrect(szPassword[])
{
  new RegEx:rPASS;

  if( !rPASS ) rPASS = regex_build("^[a-zA-Z0-9!@#\\$%\\^&*()_+-\\[\\];\\\\<>,\\.\\/?`~\"]{5,30}+$");

  if(regex_match_exid(szPassword, rPASS)) return true;
  else return false;
}

stock bool:IsHex(szHex[])
{
  new RegEx:rHEX;

  if( !rHEX ) rHEX = regex_build("^[0-9A-Fa-f]{1,6}+$");

  if(regex_match_exid(szHex, rHEX)) return true;
  else return false;
}

stock bool:IsCorrectWordForCensorship(szWord[])
{
  new RegEx:rWORD;

  if( !rWORD ) rWORD = regex_build("^[0-9A-Za-z]{1,30}+$");

  if(regex_match_exid(szWord, rWORD)) return true;
  else return false;
}