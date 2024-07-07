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

//
// $Id: ArchiveTimeForm.h,v 1.6 1999/04/30 01:44:04 kenmcd Exp $
//
//////////////////////////////////////////////////////////////
//
// Header file for ArchiveTimeForm
//
//    This file is generated by RapidApp 1.1
//
//    This class is derived from ArchiveTimeFormUI which 
//    implements the user interface created in 
//    the interface builder. This class contains virtual
//    functions that are called from the user interface.
//
//    When you modify this header file, limit your changes to adding
//    members below the "//--- End generated code section" markers
//
//    This will allow the builder to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//////////////////////////////////////////////////////////////
#ifndef ARCHIVETIMEFORM_H
#define ARCHIVETIMEFORM_H
#include "ArchiveTimeFormUI.h"

#include <Vk/VkWindow.h>
#include <Vk/VkMenuBar.h>
#include <Vk/VkSubMenu.h>
#include <Vk/VkInput.h>

//---- End generated headers

#include "../timer/VkPCPtimer.h"
#include "pmapi.h"
#include "impl.h"
#include "tv.h"
#include "ArchiveBounds.h"

typedef enum {
    VCR_STOP, VCR_FOR_PLAY, VCR_FOR_FAST, VCR_REV_PLAY, VCR_REV_FAST
} vcrMode;

typedef enum {
    VCR_FORWARD, VCR_REVERSE
} vcrDirection;

//---- ArchiveTimeForm class declaration

class ArchiveTimeForm : public ArchiveTimeFormUI
{

  public:

    ArchiveTimeForm(const char *, Widget);
    ArchiveTimeForm(const char *);
    ~ArchiveTimeForm();
    const char *  className();
    virtual void setParent(VkWindow  *);
    void boundsActivate(Widget, XtPointer);
    void detailedPositionsValueChanged(Widget, XtPointer);
    virtual void hideButtonActivate(Widget, XtPointer);
    virtual void showYearValueChanged(Widget, XtPointer);

    //--- End generated code section
    int initialize(int, int, pmTime *); /* control, client, initialState */
    void setIntervalUnits(void); /* set the interval factor */
    void setInterval(char *);	/* numeric string in current units */
    void setInterval(_pmtvTimeVal &);	/* new interval */
    void setPosition(char *);	/* time spec relative to current beginning */
    void setPosition(struct timeval *); /* absolute timeval */
    void setPosition(int percent = 0); /* percentage of beginning -> finish */
    void setSpeed(char *); /* replay rate, 1.0 is realtime */
    void setSpeed(double newSpeed = 1.0); /* replay rate, 1.0 is realtime */
    int  validateVcrMode(vcrMode);
    void setVcrMode(vcrMode, int updatePixmaps=1); /* new vcr mode, updatePixmaps=1 */
    void setIndicatorState(int); /* PM_TIME_STATE_STOP ... */
    void setBounds(struct timeval *, struct timeval *);
    void showDialog(int, int notifyClients=1);
    void vcrStep(vcrDirection);
    void showPosition(void);
    void showInterval(void);
    void showSpeed(void);
    void syncAcks(int);
    void addTimezone(char *, char *);
    void setTimezone(char *); /* label */
    void timezoneValueChanged(Widget, XtPointer);
    inline vcrMode getVcrMode() {return _vcrMode;}
    void boundsChangedCB(VkCallbackObject *obj, void *clientData, void *callData);

  protected:


    // These functions will be called as a result of callbacks
    // registered in ArchiveTimeFormUI

    void intervalActivate ( Widget, XtPointer );
    void intervalUnitsActivate ( Widget, XtPointer );
    void intervalValueChanged ( Widget, XtPointer );
    void positionActivate ( Widget, XtPointer );
    void positionScaleDrag ( Widget, XtPointer );
    void positionScaleValueChanged ( Widget, XtPointer );
    void positionValueChanged ( Widget, XtPointer );
    void speedActivate ( Widget, XtPointer );
    void speedThumbDrag ( Widget, XtPointer );
    void speedThumbValueChanged ( Widget, XtPointer );
    void speedValueChanged ( Widget, XtPointer );
    void vcrActivate ( Widget, XtPointer );
    void vcrOptionActivate ( Widget, XtPointer );

    VkWindow * _parent;
    //--- End generated code section

    ArchiveBounds *_archiveBounds;

  private:

    //--- End generated code section
    vcrMode _vcrMode;
    __pmTimeState *_state;
    int _control;
    double _currentSpeed;
    vcrDirection _currentDir;
    int _runningSlow;

    VkInput *_clientHandler;
    void newClientCallback(VkCallbackObject *, void *, void *);
    void clientReadyCallback(VkCallbackObject *, void *, void *);

    VkPCPtimer *_timer;
    void timerCallback(VkCallbackObject *, void *, void *);


    int _detailedPositions;
    int _showYear;

    // these are used when the interval is changed/recalculated.
    // The calcs should be re-done before each use. This is done
    // by the setIntervalUnits operator.
    char 	*ival_fmt;
    _pmtvUnits	ival_units;

};
#endif
