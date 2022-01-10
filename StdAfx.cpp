// stdafx.cpp : source file that includes just the standard includes
//	DragonRaja.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

#ifdef KOREAN_LOCALIZING_

const char szConnectionErr[] = "���� ������ġ ������ ������Ʈ �� �̰ų� ȸ�� ���°� ���� �ʽ��ϴ�.\n"
                               "�����⸦ ����Ͻô� ���� �����⸦ ���� �Ͻð� ��ġ�ޱ⸦ �õ� �Ͻðų�,\n"
							   "Ȩ���������� �ֽ� ��ġ ������ �޾� ��ġ �Ͻ� �� �ٽ� ���� �Ͻñ� �ٶ��ϴ�.";
const char szIniReadErr[] = "������� �ٽ� ���� �� ���ʽÿ�.(Error INI)";
const char szTxtReadErr[] = "������� �ٽ� ���� �� ���ʽÿ�.(Error Txt)";
const char szTxtAuthConnectErr[] = "�������� ������ ���� �Ͽ����ϴ�.";

const char szFileDownErr[] = "���� ������ġ ������ ������Ʈ �� �̰ų� ȸ�� ���°� ���� �ʽ��ϴ�."
							 "��Ȱ�� �ٿ�ε带 ���ؼ� PC ������� ������ �帳�ϴ�";
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
const char szConnectionErr[] = "�����A�I?�g�p�b?�T?�o?���A�b�v�f?�g��������̏�Ԃ��悭�Ȃ����ߐڑ��ł��܂���\n"
                               "��??�����g�p�Ȃ����Ă�����́A���̃�??���������Ă���p�b?��?�E����?�h�����݂Ă��������B\n"
							   "�Ȃ��A����ł�?�E����?�h�����܂��ł��Ȃ��ꍇ�́ANGC�z??�y?�W����ŐV�p�b?�t?�C����?�E����?�h���ăC���X�g?�����Ă��������B";
const char szIniReadErr[] = "�ċN�����Ă���A������x���s���Ă��������B(Error INI)";
const char szTxtReadErr[] = "�ċN�����Ă���A������x���s���Ă��������B(Error Txt)";
const char szTxtAuthConnectErr[] = "�F�؃T?�o?�ւ̃A�N�Z�X�Ɏ��s���܂����B";

const char szFileDownErr[] = "�����A�I?�g�p�b?�T?�o?���A�b�v�f?�g��������̏�Ԃ��悭�Ȃ����ߐڑ��ł��܂���B"
							 "?����?�E����?�h�̂��߁A�p?�R���̍ċN���������߂������܂��B";
*/
#endif