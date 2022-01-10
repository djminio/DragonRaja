// stdafx.cpp : source file that includes just the standard includes
//	DragonRaja.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef KOREAN_LOCALIZING_

const char szConnectionErr[] = "현재 오토패치 서버가 업데이트 중 이거나 회선 상태가 좋지 않습니다.\n"
                               "공유기를 사용하시는 분은 공유기를 해제 하시고 패치받기를 시도 하시거나,\n"
							   "홈페이지에서 최신 패치 파일을 받아 설치 하신 후 다시 실행 하시기 바랍니다.";
const char szIniReadErr[] = "재부팅후 다시 실행 해 보십시요.(Error INI)";
const char szTxtReadErr[] = "재부팅후 다시 실행 해 보십시요.(Error Txt)";
const char szTxtAuthConnectErr[] = "인증서버 접근이 실패 하였습니다.";

const char szFileDownErr[] = "현재 오토패치 서버가 업데이트 중 이거나 회선 상태가 좋지 않습니다."
							 "원활한 다운로드를 위해서 PC 재부팅을 권장해 드립니다";
#endif                             

#if defined (USA_LOCALIZING_) || defined (TAIWAN_LOCALIZING_) || defined (CHINA_LOCALIZING_) || defined (HONGKONG_LOCALIZING_)|| defined (JAPAN_LOCALIZING_)

const char szConnectionErr[] = "AutoPatch server is being updating now, or line status is not good.\n"
                               "If you use IP-sharing feature, please shut down the function and try again, \n"
							   "or download the new patch file from our homepage, and try again after installing the new patch.";
const char szIniReadErr[] = "Please reboot and try again.(Error INI)";
const char szTxtReadErr[] = "Please reboot and try again.(Error TXT)";
const char szTxtAuthConnectErr[] = "Fail to access to download authorization server.";

const char szFileDownErr[] = "AutoPatch server is being updating now, or line staus is not good.\n"
							 "We recommend you to reboot your PC for better download";
/*
const char szConnectionErr[] = "묥뜞갂긆?긣긬긞?긖?긫?궕귺긞긵긢?긣뭷궔됷멄궻륉뫴궕귝궘궶궋궫귕먝뫏궳궖귏궧귪\n"
                               "깑??귩궟럊뾭궶궠궯궲궋귡뺴궼갂궩궻깑??귩됶룣궢궲궔귞긬긞?궻?긂깛깓?긤귩럫귒궲궘궬궠궋갃\n"
							   "궶궓갂궩귢궳귖?긂깛깓?긤궕궎귏궘궳궖궶궋뤾뜃궼갂NGC긼??긻?긙궔귞띍륷긬긞?긲?귽깑귩?긂깛깓?긤궢궲귽깛긚긣?깑궢궲궘궬궠궋갃";
const char szIniReadErr[] = "띋딳벍궢궲궔귞갂귖궎덇뱗렳뛱궢궲궘궬궠궋갃(Error INI)";
const char szTxtReadErr[] = "띋딳벍궢궲궔귞갂귖궎덇뱗렳뛱궢궲궘궬궠궋갃(Error Txt)";
const char szTxtAuthConnectErr[] = "봃뤪긖?긫?귉궻귺긏긜긚궸렪봲궢귏궢궫갃";

const char szFileDownErr[] = "묥뜞갂긆?긣긬긞?긖?긫?궕귺긞긵긢?긣뭷궔됷멄궻륉뫴궕귝궘궶궋궫귕먝뫏궳궖귏궧귪갃"
							 "?뒍궶?긂깛깓?긤궻궫귕갂긬?긓깛궻띋딳벍귩궓뒰귕궋궫궢귏궥갃";
*/
#endif