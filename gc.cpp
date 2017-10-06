/*
 *		Garbaage collect code
 */

#include "gc.h"

namespace GCLocal
{
	GCControl::GCControl(GCControl *head)
	{
		refcount = 0;
		sweepId = 0;
		offset = 0;
		length = 0;
		add(head);
	}

	void GCControl::remove(GCControl *head)
	{
		if (!forward)
		{
			forward->backward = backward;
		}

		if (!backward) 
		{
			head = forward;
		}
		else
		{
			backward->forward = forward;
		}
	}

	void GCControl::add(GCControl *head)
	{
		if (!head)
		{
			backward = NULL;
		}
		else
		{
			backward = head->backward;
		}

		forward = head;
		head = this;
	}

	GCControl *allocatedHead = NULL;
	GCControl *freeHead = new GCAvailable(NULL, ALLOC_SIZE);
	GCBuffer buffer = GCBuffer();
}
