#pragma once


class CReportClass
{
public:
	CReportClass();
	~CReportClass();


public:
	//void CUbiGem::ReportFn  ,ceid 보내는곳
	//void CUbiGem::OnReceivedNewECVSend ,  Host에서 S2F15(New ECV Send)가 수신될 때 발생 EC LIST

	std::string strAbortedLot;

public:
	//New 250117

	//Set.0 NO LIST 5ea
	//
	RcmdCtrlStateChgReq rCtrlState_Chg_Req;			//LGIT_CTRLSTATE_CHG_REQ
	RcmdOpCall rCtrlOp_Call;						//LGIT_OP_CALL
	RcmdMaterialIdConfirm rMaterial_Id_Confirm;		//LGIT_MATERIAL_ID_CONFIRM
	RcmdMaterialIdFail rMaterial_Id_Fail;			//LGIT_MATERIAL_ID_FAIL
	RcmdLgitPause rLgit_Pause;						//LGIT_PAUSE




	//Set.1 - no Child List로 Name , Val 들어온다.
	std::vector<RcmdParam1> vIdleReason;
	std::vector<RcmdParam1> vOfflineReason;
	std::vector<RcmdParam1> vModelLIst;
	std::vector<RcmdParam1> vPPUploadFail;


	//Set.2
	std::vector<RcmdParameter> vLotIdFail;
	std::vector<RcmdParameter> vPPSelect;
	std::vector<RcmdParameter> vPPUploadConfirm;


	//Set.3
	std::vector<RcmdParameter> vLotStart;
	std::vector<RcmdParameter> vMaterialExchange;



};

