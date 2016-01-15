/*
 *  OpenBangla Keyboard
 *  Copyright (C) 2015-2016 Muhammad Mominul Huque <mominul2082@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "im.h"
#include "log.h"
#include "keycode.h"
#include "methodphonetic.h"

void MethodPhonetic::setLayout(QJsonObject lay) {
  suggest.setLayout(lay);
}

std::vector<std::string> MethodPhonetic::toStdVector(QVector<QString> vec) {
  std::vector<std::string> v;
  for(auto& str : vec) {
    v.push_back(str.toStdString());
  }
  return v;
}

void MethodPhonetic::updateCache() {
  // Our Suggestion builder
  if(EnglishT == "") {
    // If there is no text available, don't do anything
    return;
  } else {
    // Something we have to build
    list = suggest.Suggest(EnglishT);
    im_update_suggest(toStdVector(list), EnglishT.toStdString());
    // Is user selected any candidate before?
    QString selected = suggest.getPrevSelected();
    if(selected != "") {
      // User has selected a candidate before
      int index = list.indexOf(selected);
      if(index != -1) {
        im_selectCandidate(index);
      }
    }
  }
}

void MethodPhonetic::commitCandidate() {
  int selected = im_get_selection_id();
  if(selected != 0) {
    // User selected other candidates than the default no 0 candidate
    QString candidate = QString::fromStdString(im_get_selection(selected));
    suggest.saveSelection(candidate);
  } else {
    // User selected default one.
    // Check if the user want to go back to the default candidate
    if(suggest.getPrevSelected() != "") {
      suggest.removeSelection();
    }
  }
  im_commit();
}

bool MethodPhonetic::processKey(int key, bool shift, bool altgr, bool shiftaltgr) {
  switch(key) {
    // Begin Alphanumeric Zone
    case VC_BACKQUOTE:
    if(shift) {
      EnglishT += "~";
      updateCache();
      return true;
    } else if(!shift) {
      EnglishT += "`";
      updateCache();
      return true;
    } else if(altgr || shiftaltgr) {
      return false;
    }
    break;

    case VC_1:
      if(shift) {
        EnglishT += "!";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "1";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_2:
      if(shift) {
        EnglishT += "@";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "2";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_3:
      if(shift) {
        EnglishT += "#";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "3";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_4:
      if(shift) {
        EnglishT += "$";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "4";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_5:
      if(shift) {
        EnglishT += "%";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "5";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_6:
      if(shift) {
        EnglishT += "^";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "6";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_7:
      if(shift) {
        EnglishT += "&";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "7";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_8:
      if(shift) {
        EnglishT += "*";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "8";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
    case VC_9:
      if(shift) {
        EnglishT += "(";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "9";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_0:
      if(shift) {
        EnglishT += ")";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "0";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }

   case VC_MINUS:
      if(shift) {
        EnglishT += "_";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "-";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
   case VC_EQUALS:
      if(shift) {
        EnglishT += "+";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "=";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
   case VC_BACKSPACE:
      if(EnglishT.length() > 0) {
        QString ET = EnglishT.mid(0, EnglishT.length()-1);
        EnglishT = ET;
        updateCache();
        if(EnglishT.length() <= 0) {
          im_reset();
        }
        return true;
      } else {
        return false;
      }
      break;

   case VC_A:
      if(shift) {
        EnglishT += "A";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "a";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_B:
      if(shift) {
        EnglishT += "B";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "b";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_C:
      if(shift) {
        EnglishT += "C";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "c";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_D:
      if(shift) {
        EnglishT += "D";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "d";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_E:
      if(shift) {
        EnglishT += "E";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "e";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_F:
      if(shift) {
        EnglishT += "F";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "f";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_G:
      if(shift) {
        EnglishT += "G";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "g";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_H:
      if(shift) {
        EnglishT += "H";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "h";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_I:
      if(shift) {
        EnglishT += "I";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "i";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_J:
      if(shift) {
        EnglishT += "J";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "j";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_K:
      if(shift) {
        EnglishT += "K";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "k";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_L:
      if(shift) {
        EnglishT += "L";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "l";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_M:
      if(shift) {
        EnglishT += "M";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "m";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_N:
      if(shift) {
        EnglishT += "N";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "n";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_O:
      if(shift) {
        EnglishT += "O";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "o";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_P:
      if(shift) {
        EnglishT += "P";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "p";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_Q:
      if(shift) {
        EnglishT += "Q";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "q";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_R:
      if(shift) {
        EnglishT += "R";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "r";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_S:
      if(shift) {
        EnglishT += "S";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "s";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_T:
      if(shift) {
        EnglishT += "T";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "t";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
   case VC_U:
      if(shift) {
        EnglishT += "U";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "u";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_V:
      if(shift) {
        EnglishT += "V";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "v";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_W:
      if(shift) {
        EnglishT += "W";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "w";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_X:
      if(shift) {
        EnglishT += "X";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "x";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_Y:
      if(shift) {
        EnglishT += "Y";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "y";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_Z:
      if(shift) {
        EnglishT += "Z";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "z";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;

   case VC_OPEN_BRACKET:
      if(shift) {
        EnglishT += "{";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "[";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_CLOSE_BRACKET:
      if(shift) {
        EnglishT += "}";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "]";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_BACK_SLASH:
      if(shift) {
        EnglishT += "|";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "\\";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;

   case VC_SEMICOLON:
      if(shift) {
        EnglishT += ":";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += ";";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_QUOTE:
      if(shift) {
        EnglishT += "\"";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "\'";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_ENTER:
      if(EnglishT.length() > 0) {
        commitCandidate();
        EnglishT = "";
        return false; // Close candidate window and ungrab the event
      } else {
        return false;
      }

   case VC_COMMA:
      if(shift) {
        EnglishT += "<";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += ",";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_PERIOD:
      if(shift) {
        EnglishT += ">";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += ".";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;
   case VC_SLASH:
      if(shift) {
        EnglishT += "?";
        updateCache();
        return true;
      } else if(!shift) {
        EnglishT += "/";
        updateCache();
        return true;
      } else if(altgr || shiftaltgr) {
        return false;
      }
      break;

   case VC_SPACE:
      if(EnglishT.length() > 0) {
        commitCandidate();
        EnglishT = "";
        return false; // Close candidate window and ungrab the event
      } else {
        return false;
      }
      break;
   // End Alphanumeric Zone

   // Begin Cursor Key Zone
   case VC_UP:
      if(EnglishT.length() > 0) {
        im_table_sel_inc();
        return true;
      } else {
        return false;
      }
      break;
   case VC_RIGHT:
      if(EnglishT.length() > 0) {
        im_table_sel_inc();
        return true;
      } else {
        return false;
      }
      break;
   case VC_DOWN:
      if(EnglishT.length() > 0) {
        im_table_sel_dec();
        return true;
      } else {
        return false;
      }
      break;
   case VC_LEFT:
      if(EnglishT.length() > 0) {
        im_table_sel_dec();
        return true;
      } else {
        return false;
      }
      break;
   // End Cursor Key Zone

   // Begin Numeric Zone
   case VC_KP_DIVIDE:
      if(shift || altgr || shiftaltgr) {
        return false;
      } else {
        EnglishT += "/";
        updateCache();
        return true;
      }
      break;
   case VC_KP_MULTIPLY:
      if(shift || altgr || shiftaltgr) {
        return false;
      } else {
        EnglishT += "*";
        updateCache();
        return true;
      }
      break;
   case VC_KP_SUBTRACT:
      if(shift || altgr || shiftaltgr) {
        return false;
      } else {
        EnglishT += "-";
        updateCache();
        return true;
      }
      break;
   case VC_KP_ADD:
      if(shift || altgr || shiftaltgr) {
        return false;
      } else {
        EnglishT += "+";
        updateCache();
        return true;
      }
      break;
   case VC_KP_ENTER:
      if(EnglishT.length() > 0) {
        commitCandidate();
        EnglishT = "";
        return false; // Close candidate window and ungrab the event
      } else {
        return false;
      }
      break;
   case VC_KP_DECIMAL:
      if(shift || altgr || shiftaltgr) {
        return false;
      } else {
        EnglishT += ".";
        updateCache();
        return true;
      }
      break;

   case VC_KP_1:
      if(!shift) {
        EnglishT += "1";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_2:
      if(!shift) {
        EnglishT += "2";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_3:
      if(!shift) {
        EnglishT += "3";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_4:
      if(!shift) {
        EnglishT += "4";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_5:
      if(!shift) {
        EnglishT += "5";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_6:
      if(!shift) {
        EnglishT += "6";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_7:
      if(!shift) {
        EnglishT += "7";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_8:
      if(!shift) {
        EnglishT += "8";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_9:
      if(!shift) {
        EnglishT += "9";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   case VC_KP_0:
      if(!shift) {
        EnglishT += "0";
        updateCache();
        return true;
      } else {
        return false;
      }
      break;
   // End Numeric Zone

   case VC_UNKNOWN:
      return false;
      break;
   default:
      return false;
   }
 }
