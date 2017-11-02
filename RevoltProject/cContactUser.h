#pragma once
class cContactUser : public NxUserContactReport
{
public:
	cContactUser();
	virtual ~cContactUser();

	void onContactNotify(NxContactPair& pair, NxU32 events);
};

