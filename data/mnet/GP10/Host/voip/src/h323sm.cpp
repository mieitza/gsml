
/*
 ****************************************************************************************
 *																						*
 *			Copyright Cisco Systems, Inc 2000 All rights reserved						*
 *																						*
 *--------------------------------------------------------------------------------------*
 *																						*
 *	File				: H323SM.cpp													*
 *																						*
 *	Description			: State Machine table for the H.323 task						*
 *																						*
 *	Author				: Dinesh Nambisan												*
 *																						*
 *----------------------- Revision history ---------------------------------------------*
 * Time  | Date    | Name   | Description 												*
 *--------------------------------------------------------------------------------------*
 * 00:00 |03/24/99 | DSN    | File created												*
 *		 |		   |		|															*
 *		 |		   |	    |															*
 ****************************************************************************************
 */


#include <stdlib.h>
#include <string.h>
#include <cm.h>
#include <stkutils.h>
#include <tickLib.h>
#include <drv\timer\timerDev.h>
#include <taskLib.h>


#include "h323task.h"
#include "ccb.h"
#include "util.h"
#include "eventhandlers.h"
#include "rtptask.h"
#include "smroutines.h"


#define INVALID_EVENT \
{ \
  smFatalStateMachineViolation, \
  H323_CALL_STATE_IDLE \
}

#define DISCARD_EVENT \
{ \
  smNonFatalStateMachineViolation, \
  H323_CALL_STATE_SAME_STATE \
}




/*
 *
 *  The state machine table: This can be modified as and when required:DSN
 */
H323_CALL_STATE_INFO
H323_CALL_STATE_TABLE
[H323_MAX_CALL_STATES][H323_MAX_CALL_EVENTS] = {

	/* BEGIN: State = H323_CALL_STATE_IDLE */
	{
		{
			smCallOffering,				/* H323_EVENT_RECV_CALL_OFFERING */
			H323_CALL_STATE_WAIT_FOR_CC_ANSWER
		},

		DISCARD_EVENT,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
		DISCARD_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		{
			smCallSetup,				/* H323_EVENT_RECV_CC_CALL_SETUP */
			H323_CALL_STATE_WAIT_FOR_PROCEEDING
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		{
			smCallIdle,					/* H323_EVENT_RECV_CALL_IDLE */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		DISCARD_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		DISCARD_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		DISCARD_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_IDLE */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CC_ANSWER */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		{
			smAnswerCall,				/* H323_EVENT_RECV_CC_ANSWER_CALL */
			H323_CALL_STATE_WAIT_FOR_CONNECTION
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CC_ANSWER */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_PROCEEDING */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		{
			smCallProceeding,			/* H323_EVENT_RECV_CALL_PROCEEDING */
			H323_CALL_STATE_WAIT_FOR_CONNECTION
		},
		{
		    smCallRingBack,				/* H323_EVENT_RECV_CALL_RINGBACK */
            H323_CALL_STATE_SAME_STATE
        },
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		{
			smCallDestinationRejected,	/* H323_EVENT_RECV_CALL_DEST_REJECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_PROCEEDING */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CONNECTION */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		{
		    smCallRingBack,				/* H323_EVENT_RECV_CALL_RINGBACK */
            H323_CALL_STATE_SAME_STATE
        },
		{
			smCallConnected,			/* H323_EVENT_RECV_CALL_CONNECTED */
			H323_CALL_STATE_CALL_CONNECTED
		},
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CONNECTION */

	/* BEGIN: State = H323_CALL_STATE_CALL_CONNECTED */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		{
			smH245TransportConnected,	/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
			H323_CALL_STATE_WAIT_FOR_CAP_EXCHANGE_ACK
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_CALL_CONNECTED */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CAP_EXCHANGE_ACK */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		{
			smRecvRemoteCapabilities,	/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		{
			smH245Connected,			/* H323_EVENT_RECV_H245_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smRecvCapabilitiesAck,		/* H323_EVENT_RECV_CAPABILITIES_ACK */
			H323_CALL_STATE_WAIT_FOR_CHANNELS_CONNECTION
		},
		{
			smRecvCapabilitiesNak,		/* H323_EVENT_RECV_CAPABILITIES_NAK */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CAP_EXCHANGE_ACK */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CHANNELS_CONNECTION */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		{
			smH245Connected,			/* H323_EVENT_RECV_H245_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		{
			smChannelOffering,			/* H323_EVENT_RECV_CHANNEL_OFFERING */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelConnected,		/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelConnected,		/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
			H323_CALL_STATE_CHANNELS_CONNECTED
		},
		{
			smInChannelDisconnected,	/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelDisconnected,	/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CHANNELS_CONNECTION */

	/* BEGIN: State = H323_CALL_STATE_CHANNELS_CONNECTED */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		{
			smChannelOffering,			/* H323_EVENT_RECV_CHANNEL_OFFERING */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelConnected,		/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelConnected,		/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
			H323_CALL_STATE_CHANNELS_CONNECTED
		},
		{
			smInChannelDisconnected,	/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelDisconnected,	/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		}
	}/* END: State = H323_CALL_STATE_CHANNELS_CONNECTED */

};








/*
 *
 *  The Fast Setup state machine table: This can be modified as and when required:DSN
 */
H323_CALL_STATE_INFO
H323_FASTCALL_STATE_TABLE
[H323_MAX_CALL_STATES][H323_MAX_CALL_EVENTS] = {

	/* BEGIN: State = H323_CALL_STATE_IDLE */
	{
		{
			smCallOffering,				/* H323_EVENT_RECV_CALL_OFFERING */
			H323_CALL_STATE_WAIT_FOR_CC_ANSWER
		},

		DISCARD_EVENT,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
		DISCARD_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		{
			smCallSetup,				/* H323_EVENT_RECV_CC_CALL_SETUP */
			H323_CALL_STATE_WAIT_FOR_PROCEEDING
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		{
			smCallIdle,					/* H323_EVENT_RECV_CALL_IDLE */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		DISCARD_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		DISCARD_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		DISCARD_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_IDLE */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CC_ANSWER */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		{
			smAnswerCall,				/* H323_EVENT_RECV_CC_ANSWER_CALL */
			H323_CALL_STATE_WAIT_FOR_CONNECTION
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		{
			smChannelOffering,			/* H323_EVENT_RECV_CHANNEL_OFFERING */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelConnected,		/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelConnected,		/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelDisconnected,	/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CC_ANSWER */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_PROCEEDING */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		{
			smCallProceeding,			/* H323_EVENT_RECV_CALL_PROCEEDING */
			H323_CALL_STATE_WAIT_FOR_CONNECTION
		},
		{
		    smCallRingBack,				/* H323_EVENT_RECV_CALL_RINGBACK */
            H323_CALL_STATE_WAIT_FOR_CONNECTION
        },
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		{
			smCallDestinationRejected,	/* H323_EVENT_RECV_CALL_DEST_REJECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_PROCEEDING */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CONNECTION */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		{
		    smCallRingBack,				/* H323_EVENT_RECV_CALL_RINGBACK */
            H323_CALL_STATE_SAME_STATE
        },
		{
			smCallConnected,			/* H323_EVENT_RECV_CALL_CONNECTED */
			H323_CALL_STATE_CHANNELS_CONNECTED
		},
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		{
			smRecvRemoteCapabilities,	/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smH245TransportConnected,	/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smH245Connected,			/* H323_EVENT_RECV_H245_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smRecvCapabilitiesAck,		/* H323_EVENT_RECV_CAPABILITIES_ACK */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smRecvCapabilitiesNak,		/* H323_EVENT_RECV_CAPABILITIES_NAK */
			H323_CALL_STATE_IDLE
		},
		{
			smChannelOffering,			/* H323_EVENT_RECV_CHANNEL_OFFERING */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelConnected,		/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelConnected,		/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelDisconnected,	/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelDisconnected,	/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CONNECTION */

	/* BEGIN: State = H323_CALL_STATE_CALL_CONNECTED */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		{
			smH245TransportConnected,	/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
			H323_CALL_STATE_WAIT_FOR_CAP_EXCHANGE_ACK
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_CALL_CONNECTED */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CAP_EXCHANGE_ACK */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		{
			smRecvRemoteCapabilities,	/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		{
			smH245Connected,			/* H323_EVENT_RECV_H245_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smRecvCapabilitiesAck,		/* H323_EVENT_RECV_CAPABILITIES_ACK */
			H323_CALL_STATE_WAIT_FOR_CHANNELS_CONNECTION
		},
		{
			smRecvCapabilitiesNak,		/* H323_EVENT_RECV_CAPABILITIES_NAK */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CHANNEL_OFFERING */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CAP_EXCHANGE_ACK */

	/* BEGIN: State = H323_CALL_STATE_WAIT_FOR_CHANNELS_CONNECTION */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		INVALID_EVENT,					/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
		INVALID_EVENT,					/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
		{
			smH245Connected,			/* H323_EVENT_RECV_H245_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_ACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CAPABILITIES_NAK */
		{
			smChannelOffering,			/* H323_EVENT_RECV_CHANNEL_OFFERING */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelConnected,		/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelConnected,		/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
			H323_CALL_STATE_CHANNELS_CONNECTED
		},
		{
			smInChannelDisconnected,	/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelDisconnected,	/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
	},/* END: State = H323_CALL_STATE_WAIT_FOR_CHANNELS_CONNECTION */

	/* BEGIN: State = H323_CALL_STATE_CHANNELS_CONNECTED */
	{
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_OFFERING */
		{
			smDropCall,					/* H323_EVENT_RECV_CC_CALL_RELEASE */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_ANSWER_CALL */
		INVALID_EVENT,					/* H323_EVENT_RECV_CC_CALL_SETUP */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_PROCEEDING */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_RINGBACK */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_CONNECTED */
		{
			smCallDisconnected,			/* H323_EVENT_RECV_CALL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		},
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_DEST_REJECTED */
		INVALID_EVENT,					/* H323_EVENT_RECV_CALL_IDLE */
		{
			smRecvRemoteCapabilities,	/* H323_EVENT_RECV_REMOTE_CAPABILITIES */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smH245TransportConnected,	/* H323_EVENT_RECV_H245_TRANSPORT_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smH245Connected,			/* H323_EVENT_RECV_H245_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smRecvCapabilitiesAck,		/* H323_EVENT_RECV_CAPABILITIES_ACK */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smRecvCapabilitiesNak,		/* H323_EVENT_RECV_CAPABILITIES_NAK */
			H323_CALL_STATE_IDLE
		},
		{
			smChannelOffering,			/* H323_EVENT_RECV_CHANNEL_OFFERING */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smInChannelConnected,		/* H323_EVENT_RECV_IN_CHANNEL_CONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelConnected,		/* H323_EVENT_RECV_OUT_CHANNEL_CONNECTED */
			H323_CALL_STATE_CHANNELS_CONNECTED
		},
		{
			smInChannelDisconnected,	/* H323_EVENT_RECV_IN_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_SAME_STATE
		},
		{
			smOutChannelDisconnected,	/* H323_EVENT_RECV_OUT_CHANNEL_DISCONNECTED */
			H323_CALL_STATE_IDLE
		}
	}/* END: State = H323_CALL_STATE_CHANNELS_CONNECTED */

};
