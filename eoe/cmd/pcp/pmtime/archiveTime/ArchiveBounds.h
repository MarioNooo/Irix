/*
 * Copyright 1997, Silicon Graphics, Inc.
 * ALL RIGHTS RESERVED
 * 
 * UNPUBLISHED -- Rights reserved under the copyright laws of the United
 * States.   Use of a copyright notice is precautionary only and does not
 * imply publication or disclosure.
 * 
 * U.S. GOVERNMENT RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to restrictions
 * as set forth in FAR 52.227.19(c)(2) or subparagraph (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS 252.227-7013 and/or
 * in similar or successor clauses in the FAR, or the DOD or NASA FAR
 * Supplement.  Contractor/manufacturer is Silicon Graphics, Inc.,
 * 2011 N. Shoreline Blvd. Mountain View, CA 94039-7311.
 * 
 * THE CONTENT OF THIS WORK CONTAINS CONFIDENTIAL AND PROPRIETARY
 * INFORMATION OF SILICON GRAPHICS, INC. ANY DUPLICATION, MODIFICATION,
 * DISTRIBUTION, OR DISCLOSURE IN ANY FORM, IN WHOLE, OR IN PART, IS STRICTLY
 * PROHIBITED WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF SILICON
 * GRAPHICS, INC.
 */


//////////////////////////////////////////////////////////////
//
// Header file for ArchiveBounds
//
//    This file is generated by RapidApp 1.2
//
//    This class is a ViewKit VkDialogManager subclass
//    See the VkDialogManager man page for info on the API
//
//    Restrict changes to those sections between
//    the "//--- Start/End editable code block" markers
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how ViewKit dialogs are used, see the
//    "ViewKit Programmers' Manual"
//
//////////////////////////////////////////////////////////////
#ifndef ARCHIVEBOUNDS_H
#define ARCHIVEBOUNDS_H
#include <Vk/VkSimpleWindow.h>

//---- Start editable code block: headers and declarations
#include <sys/time.h>

//---- End editable code block: headers and declarations



//---- ArchiveBounds class declaration

class ArchiveBounds: public VkSimpleWindow { 

  public:

    ArchiveBounds (const char *name, Widget parent);
    ~ArchiveBounds();
    const char *className();
    //---- Start editable code block:  public

    void showBounds(void);
    void addBounds(struct timeval *s, struct timeval *f, Boolean force = False);
    void setBounds(struct timeval *s, struct timeval *f);
    void getBounds(struct timeval *s, struct timeval *f);
    void getBounds(double *s, double *f);
    void setManual(Boolean manual);
    void showDetail(Boolean ms, Boolean year);
    inline Boolean isCreated(void) {return _isCreated;}
    Boolean isManual(void);
    static const char *const boundsChanged;
    void boundsChangedCB(VkCallbackObject *obj, void *clientData, void *callData);
    void cancelActivateCB(VkCallbackObject *obj, void *clientData, void *callData);
    inline virtual void handleWmDeleteMessage(void) {hide();}
    inline virtual void handleWmQuitMessage(void) {hide();}
    //---- End editable code block:  public

  protected:


    // Classes created by this class

    class ArchiveBoundsForm *_archiveBoundsMainForm2;


    //---- Start editable code block:  protected

    //---- End editable code block:  protected


  private:

    // Callbacks to interface with Motif


    //---- Start editable code block:  private
    Boolean _isCreated;
    static String  _defaultArchiveBoundsResources[];

    //---- End editable code block:  private

};

//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif
