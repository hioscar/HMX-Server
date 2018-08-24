#ifndef __SCENE_INFO_MANAGER_H_
#define __SCENE_INFO_MANAGER_H_

#include "SrvEngine.h"
#include "Single.h"

/*-------------------------------------------------------------------
 * @Brief : �����¼����������Ϣ����¼��������WS��ע������Щ����ID
 *			ͬʱ
 * @Author:hzd 2015:11:18
 *------------------------------------------------------------------*/

/*
	������̬��Ϣ id=����ID 
*/
class SceneReg : public zEntry
{
public:
	SceneReg()
	{
		id = tempid = sessid = mapid = 0;
	}

	inline uint64_t GetID(){ return id; }
	inline uint64_t GetTempID(){ return tempid; }
	inline const std::string& GetName(){ return _entry_name; }

public:
	uint64_t id;
	uint64_t tempid;
	uint64_t sessid;
	uint32_t mapid;
};


/*--
	���������� 
*/
class SceneRegMgr : protected zEntryMgr< zEntryID<0> >,public Single<SceneRegMgr>
{
protected:
	friend class Single<SceneRegMgr>;
	SceneRegMgr();
	~SceneRegMgr();

public:

	SceneReg* CreateObj();
	void DestroyObj(SceneReg* obj);

	bool add(SceneReg* scene);
	void remove(SceneReg* scene);
	SceneReg* get(int64_t id);
	SceneReg* getBymapid(int32_t mapid);// ��õ�һ��scene(ͨ��Ҳֻ��һ��scene)
	SceneReg* getFreeBymapid(int32_t mapid); // ��ñȽϿ��еĳ��� 

private:

	zObjPool<SceneReg> objpool;

};


#endif

