#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes/UGRC_EnumTypes.h"

class FUGRC_CountDownAction : public FPendingLatentAction
{
public:
	FUGRC_CountDownAction(
		float InTotalCountDownTime,
		float InUpdateInterval,
		float& InOutRemainingTime,
		EUGRC_CountDownActionOutput& InCountDownOutput,
		const FLatentActionInfo& LatentInfo	
	) :
		bNeedToCancel(false),
		TotalCountDownTime(InTotalCountDownTime),
		UpdateInterval(InUpdateInterval),
		OutRemainingTime(InOutRemainingTime),
		CountDownOutput(InCountDownOutput),
		ExecutionFunction(LatentInfo.ExecutionFunction),
		OutputLink(LatentInfo.Linkage),
		CallbackTarget(LatentInfo.CallbackTarget),
		ElapsedInterval(0.f),
		ElapsedTimeSinceStart(0.f)
	{}
	
	void CancelAction();
	
	// Begin ~FPendingLatentAction Interface
	virtual void UpdateOperation(FLatentResponse& Response) override;
	// End ~FPendingLatentAction Interface
	
private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EUGRC_CountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};