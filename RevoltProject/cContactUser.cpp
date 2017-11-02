#include "stdafx.h"
#include "cContactUser.h"


cContactUser::cContactUser()
{
}


cContactUser::~cContactUser()
{
}

void cContactUser::onContactNotify(NxContactPair & pair, NxU32 events)
{
	NxContactStreamIterator i(pair.stream);

	while (i.goNextPair())
	{
		while (i.goNextPatch())
		{
			const NxVec3& contactNormal = i.getPatchNormal();
			while (i.goNextPoint())
			{
				const NxVec3& contactPoint = i.getPoint();
			}
		}
	}

	return;
}
