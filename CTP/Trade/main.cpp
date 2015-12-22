#include "stdafx.h"
#include "../include/ApiHeader.h"
#include "../include/QueueEnum.h"
#include "TraderApi.h"

inline CTraderApi* GetApi(void* pApi)
{
	return static_cast<CTraderApi*>(pApi);
}

void* __stdcall XRequest(char type, void* pApi1, void* pApi2, double double1, double double2, void* ptr1, int size1, void* ptr2, int size2, void* ptr3, int size3)
{
	RequestType rt = (RequestType)type;
	switch (rt)
	{
	case GetApiType:
		return (void*)(ApiType::ApiType_Trade | ApiType::ApiType_Instrument | ApiType::ApiType_Query);
	case GetApiVersion:
		return (void*)API_VERSION;
	case GetApiName:
		return (void*)API_NAME;
	case Create:
		return new CTraderApi();
	default:
		break;
	}

	if (pApi1 == nullptr)
	{
		return nullptr;
	}

	CTraderApi* pApi = GetApi(pApi1);

	switch (rt)
	{
	case Release:
		delete pApi;
		return nullptr;
	case Register:
		pApi->Register(ptr1, ptr2);
		break;
	case Connect:
		pApi->Connect((const char*)ptr3, (ServerInfoField*)ptr1, (UserInfoField*)ptr2,size2);
		break;
	case Disconnect:
		pApi->Disconnect();
		break;
	case ReqQryInstrument:
	case ReqQryInvestorPosition:
	case ReqQryTradingAccount:
	case ReqQrySettlementInfo:
		pApi->ReqQuery((QueryType)type, (ReqQueryField*)ptr1);
		break;
	case ReqOrderInsert:
		return (void*)pApi->ReqOrderInsert((OrderField*)ptr1, size1, (char*)ptr2);
	case ReqQuoteInsert:
		return pApi->ReqQuoteInsert((QuoteField*)ptr1, (OrderIDType*)ptr2, (OrderIDType*)ptr3);
	case ReqOrderAction:
		return (void*)pApi->ReqOrderAction((OrderIDType*)ptr1, size1, (char*)ptr2);
	case ReqQuoteAction:
		return (void*)pApi->ReqQuoteAction((const char*)ptr1, (OrderIDType*)ptr2);
	default:
		break;
	}

	return pApi1;
}