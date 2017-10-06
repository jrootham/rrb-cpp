/*
 *		Garbage collect include file
 */

#ifndef GC
#define GC

#include <cstddef>

namespace GCLocal
{
	const size_t	ALLOC_SIZE = 2048;

	class GCBuffer
	{
	public:
		GCBuffer()
		{
			next = NULL;
			length = ALLOC_SIZE;
		}

	private:

		GCBuffer	*next;
		size_t		length;
		char		buffer[ALLOC_SIZE];
	};

	class GCControl
	{
	private:
		GCControl 	*forward;
		GCControl 	*backward;
		int			refcount;
		int			sweepId;

	protected:
		size_t 		offset;
		size_t		length;

	public:
		GCControl(GCControl *head);
		~GCControl();
		
		void remove(GCControl *head);
		void add(GCControl *head);

		void link()
		{
			refcount++;
		}

		void unlink(GCControl *allocatedHead, GCControl *freeHead)
		{
			if (--refcount  <= 0) 
			{
				remove(allocatedHead);
				add(freeHead);
			}
		}
	};

	class GCBase
	{
	private:
		GCControl	*control;

	public:
		 GCBase();
		~ GCBase();
		
	};
	void unlink(GCBase *base);

	class GCAvailable : public GCControl
	{
	public:
		 GCAvailable(GCControl *head, size_t amount) : GCControl(head)
		 {
		 	offset = 0;
		 	length = amount;
		 }

		 void deallocate(size_t amount)
		 {
		 	offset += amount;
		 	length -= amount;
		 }
	};
}

#endif
