/* Layout file created by tedit */

#ifndef TUDONTAUTOINCLUDE
#include "tuGap.h"
#include "tuLabel.h"
#include "tuBBoard.h"
#include "tuRowColumn.h"
#include "tuFrame.h"
#include "tuDeck.h"
#endif /* TUDONTAUTOINCLUDE */

#ifdef TUREGISTERGADGETS
#undef TUREGISTERGADGETS
#endif /* TUREGISTERGADGETS */
#define TUREGISTERGADGETS { \
    tuGap::registerForPickling(); \
    tuLabel::registerForPickling(); \
    tuBBoard::registerForPickling(); \
    tuRowColumn::registerForPickling(); \
    tuFrame::registerForPickling(); \
    tuDeck::registerForPickling(); \
}

static char* layoutstr =
"(Frame "
 "(resources "
  "((frame Innie))) "
 "(child "
  "(Deck "
   "(instanceName deck) "
   "(child "
    "(RowColumn "
     "(instanceName absChild) "
     "(rows 3) "
     "(cols 2) "
     "(defaultAlignment 0) "
     "(resources "
      "((leftInset 10) "
       "(rightInset 10) "
       "(horizontalOffset 10) "
       "(fixedHeight True))) "
     "(child "
      "(Gap "
       "(orientation horizontal) "
       "(resources "
        "((minWidth 200))))) "
     "(constraint R0C0A0) "
     "(child "
      "(Gap "
       "(orientation vertical))) "
     "(constraint R0C1A0) "
     "(child "
      "(RowColumn "
       "(rows 2) "
       "(cols 3) "
       "(defaultAlignment 0) "
       "(resources "
        "((fixedHeight True))) "
       "(child "
        "(BBoard "
         "(child "
          "(Label "
           "(instanceName leftTimeLabel) "
           "(resources "
            "((labelString 88:88:88x) "
             "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
         "(constraint 70x15+0+0))) "
       "(constraint R0C0A8) "
       "(child "
        "(BBoard "
         "(child "
          "(RowColumn "
           "(rows 1) "
           "(cols 2) "
           "(defaultAlignment 2) "
           "(resources "
            "((fixedWidth True))) "
           "(child "
            "(Label "
             "(instanceName rightTimeLabel) "
             "(resources "
              "((labelString 88:88:88xx) "
               "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
           "(constraint R0C1A2))) "
         "(constraint 78x15+0+0))) "
       "(constraint R0C2A0) "
       "(child "
        "(Label "
         "(instanceName leftDateLabel) "
         "(resources "
          "((labelString Jan\\ 1) "
           "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
       "(constraint R1C0A0) "
       "(child "
        "(Label "
         "(instanceName rightDateLabel) "
         "(resources "
          "((labelString Dec\\ 31) "
           "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
       "(constraint R1C2A2))) "
     "(constraint R1C0A0) "
     "(child "
      "(Gap "
       "(orientation vertical) "
       "(resources "
        "((minHeight 10))))) "
     "(constraint R1C1A0) "
     "(child "
      "(Label "
       "(resources "
        "((labelString Time) "
         "(font -*-helvetica-bold-r-normal--14-*-*-*-p-82-iso8859-1))))) "
     "(constraint R2C0A1) "
     "(child "
      "(RowColumn "
       "(rows 1) "
       "(cols 1) "
       "(defaultAlignment 0) "
       "(resources "
        "((fixedWidth True))) "
       "(child "
        "(Gap "
         "(orientation horizontal) "
         "(resources "
          "((minWidth 70))))) "
       "(constraint R0C0A0))) "
     "(constraint R2C1A0))) "
   "(child "
    "(RowColumn "
     "(instanceName scrollChild) "
     "(rows 3) "
     "(cols 2) "
     "(defaultAlignment 0) "
     "(resources "
      "((leftInset 10) "
       "(rightInset 10) "
       "(horizontalOffset 10) "
       "(fixedHeight True))) "
     "(child "
      "(Gap "
       "(orientation horizontal) "
       "(resources "
        "((minWidth 200))))) "
     "(constraint R0C0A0) "
     "(child "
      "(Gap "
       "(orientation vertical))) "
     "(constraint R0C1A0) "
     "(child "
      "(Frame "
       "(instanceName GLparent) "
       "(resources "
        "((frame Innie2))))) "
     "(constraint R1C0A0) "
     "(child "
      "(Gap "
       "(orientation vertical) "
       "(resources "
        "((minHeight 15))))) "
     "(constraint R1C1A0) "
     "(child "
      "(Label "
       "(resources "
        "((labelString Time) "
         "(font -*-helvetica-bold-r-normal--14-*-*-*-p-82-iso8859-1))))) "
     "(constraint R2C0A1) "
     "(child "
      "(RowColumn "
       "(rows 1) "
       "(cols 1) "
       "(defaultAlignment 0) "
       "(resources "
        "((fixedWidth True))) "
       "(child "
        "(Gap "
         "(orientation horizontal) "
         "(resources "
          "((minWidth 70))))) "
       "(constraint R0C0A0))) "
     "(constraint R2C1A0))) "
   "(child "
    "(RowColumn "
     "(instanceName relChild) "
     "(rows 3) "
     "(cols 2) "
     "(defaultAlignment 0) "
     "(resources "
      "((leftInset 10) "
       "(rightInset 10) "
       "(horizontalOffset 10) "
       "(fixedHeight True))) "
     "(child "
      "(Gap "
       "(orientation horizontal) "
       "(resources "
        "((minWidth 200))))) "
     "(constraint R0C0A0) "
     "(child "
      "(Gap "
       "(orientation vertical))) "
     "(constraint R0C1A0) "
     "(child "
      "(RowColumn "
       "(rows 1) "
       "(cols 5) "
       "(defaultAlignment 0) "
       "(resources "
        "((fixedHeight True))) "
       "(child "
        "(Label "
         "(instanceName relLeftTimeLabel) "
         "(resources "
          "((labelString -60) "
           "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
       "(constraint R0C0A0) "
       "(child "
        "(Label "
         "(instanceName relMidTimeLabel) "
         "(resources "
          "((labelString -30) "
           "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
       "(constraint R0C2A0) "
       "(child "
        "(Label "
         "(instanceName ) "
         "(resources "
          "((labelString 0) "
           "(font -*-screen-medium-r-normal--16-*-*-*-m-80-iso8859-1))))) "
       "(constraint R0C4A2))) "
     "(constraint R1C0A7) "
     "(child "
      "(Gap "
       "(orientation vertical) "
       "(resources "
        "((minHeight 15))))) "
     "(constraint R1C1A0) "
     "(child "
      "(Label "
       "(instanceName relUnitLabel) "
       "(resources "
        "((labelString Time\\ in\\ seconds) "
         "(font -*-helvetica-bold-r-normal--14-*-*-*-p-82-iso8859-1))))) "
     "(constraint R2C0A1) "
     "(child "
      "(RowColumn "
       "(rows 1) "
       "(cols 1) "
       "(defaultAlignment 0) "
       "(resources "
        "((fixedWidth True))) "
       "(child "
        "(Gap "
         "(orientation horizontal) "
         "(resources "
          "((minWidth 70))))) "
       "(constraint R0C0A0))) "
     "(constraint R2C1A0))))))";