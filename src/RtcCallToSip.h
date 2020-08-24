/*
 *  Copyright (c) 2020 The anyRTC project authors. All Rights Reserved.
 *
 *  Website: https://www.anyrtc.io for more details.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */
#ifndef __RTC_CALL_TO_SIP_H__
#define __RTC_CALL_TO_SIP_H__
#include "SipCall.h"
#include "RtcCall.h"

class RtcCallToSipEvent
{
public:
	RtcCallToSipEvent(void) {};
	virtual ~RtcCallToSipEvent(void) {};

	// ���н���
	virtual void OnRtcCallToSipClosed(const std::string&strCallerId, int nCode) = 0;
};

/** RtcCallToSip��
 * ʵ��Rtc��������Sip�����ݻ�ͨ
 * 
 */
class RtcCallToSip : public RtcCall, public SipCallEvent
{
public:
	RtcCallToSip(RtcCallToSipEvent&callback);
	virtual ~RtcCallToSip(void);

	void SetCallerId(const std::string&strCallerId) { str_caller_id_ = strCallerId; };
	const std::string&SipAccount() { return str_sip_account_; };

	void InitSipAccount(const std::string&strSvrIp, int nPort, const std::string&strAccount, const std::string&strPwd);
	void StartTask(const std::string&strAppId, const std::string&strChanId, const std::string&strSipNumber, const std::string&strSipData);
	void StopTask();

	//* For RtcCall
	virtual void OnRtcCallAudioMixData(const char*pData, int nLen, int nSampleHz, int nChannels, uint32_t timestamp);

	//* For SipCallEvent
	virtual void OnRegState(bool Ok);
	virtual void OnCallOk();
	virtual void OnCallHangUp();
	virtual void OnCallAudioData(const char*pData, int nLen, int nSampleHz, int nChannels);

private:
	SipCall	*sip_call_;
	RtcCallToSipEvent &callback_;
	bool	task_started_;
	std::string str_caller_id_;
	std::string str_sip_svr_;
	std::string str_sip_account_;
	std::string str_sip_number_;
	std::string str_sip_data_;
};

#endif	// __RTC_CALL_TO_SIP_H__

