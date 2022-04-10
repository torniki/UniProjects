//---------------------------------------------------------------------------
// ������ ���������� �������� ���������� ���������, ������ 2.0 (win32)
// Copyright (C) 2003-2006 by Voverkill
//---------------------------------------------------------------------------
#ifndef __POLSTR_H__
#define __POLSTR_H__
//---------------------------------------------------------------------------
#define ERR_OK             0
#define ERR_SYNTAX_ERROR   1
#define ERR_BAD_ARGUMENT   2
#define ERR_STACK_ERROR    3
#define ERR_INVALID_PARAM  4
#define ERR_HUGE_VALUE     5
#define ERR_UNKNOWN_DER    6
#define ERR_OUT_OF_MEMORY  7
//---------------------------------------------------------------------------
// ��������� ������:
// � ERR_OK            - ������ ���;
// � ERR_SYNTAX_ERROR  - �������������� ������;
// � ERR_BAD_ARGUMENT  - �������� ������ � ���������;
// � ERR_STACK_ERROR   - � ����� ��� ����������� ������ (������ ��� ���������
//                       �������������� ������);
// � ERR_INVALID_PARAM - �������� �������� � ��������� (������� ���������,
//                       ����������� �� ��������������� ��������� � �.�.);
// � ERR_HUGE_VALUE    - �������� ��������� �� ����� ��� ������� �� �����
//                       ���� double;
// � ERR_UNKNOWN_DER   - ����������� �� ����� ���� ���������;
// � ERR_OUT_OF_MEMORY - �� ������� ������������ ������.
// ���� ������ ���� ���������, �������� �������� ����� ������.
extern int Error;
//---------------------------------------------------------------------------
// �������������� ��������� � �������� �������� ������ (���). ��������� �����
// ��������� �������� ���������, ����� PI � E, ��������� (x ��� ����������,
// x1..xn ��� ���������� n-������� ���������), ������ � ��������� ��������:
// � +   (�������� ��� ������� ����);
// � -   (��������� ��� ������� �����);
// � *   (���������);
// � /   (�������);
// � ^   (���������� � �������);
// � sin (�����);
// � cos (�������);
// � tg  (�������);
// � ctg (���������);
// � exp (���������������� �������, exp x = e^x);
// � ln  (����������� ��������);
// � lg  (�������� �� ��������� 10).
// ������� �������� �� �����. ������ ����� ������� �� ������ ���������
// ������� �� ����������� (��������, ����� ��������� ���������: cos 2,
// exp(x), sin (x + pi)). ����� �������������� � ��� ����� �����������
// ��������� �������:
// � s - sin;
// � c - cos;
// � t - tg;
// � z - ctg;
// � e - exp;
// � l - ln;
// � g - lg;
// � n - ������� �����;
// � p - ������� ����;
// � q - ����� e;
// � w - ����� pi.
// ����� ��������, �������� ��������� � ��������� �������� ��� ���������.
// ������ ���������. ���������:
// 1) char *expr - ��������� �� ������, ���������� �������� ���������;
// 2) char *pstr - ��������� �� ������, � ������� ����� �������� ���������
//    � ���� ��� (���� ����� NULL, ������ �� �����������, ������� ������
//    ��������� �� �����);
// 3) unsigned arg_count - ���������� ���������� � ��������� (���� ��������
//    ���������, ������ ���� ����� ����).
// ������������ �������� - ����� ���. ��������� ����������� �� ��� ���, ����
// �� ���������� ������ ����� ������, ������ ";" ��� �� ��������� ������.
// ���� � �������� �������������� �������� ������, ��� ����� ������������ ��
// ���������. ������� �� ����������� ������!
extern unsigned StrToPolStr (char *, char *, unsigned);
//---------------------------------------------------------------------------
// �������� ���. ���������:
// 1) char *expr - ��������� �� ������, ���������� �������� ���������;
// 2) unsigned arg_count - ���������� ���������� � ���������.
// ������ ������� ������ ������� �������� ������� StrToPolStr, �����
// ��������� ����� ���, ����� �������� ����������� ��� �������� ��� ������ �
// ����� �������� StrToPolStr ��� ������������ ���. ������ ����������
// �����������, ������� �� �������� ���������� �� ���������� delete [].
extern char *CreatePolStr (char *, unsigned);
//---------------------------------------------------------------------------
// ���������� ��������� (��������� ��������). ���������:
// 1) char *expr - ��������� �� ������, ���������� ���������;
// 2) double arg - �������� ���������;
// 3) unsigned der - ������� ����������� (0 - �� ��������� - ���������
//    ���������, 1 - ������ �����������, 2 - ������ ����������� � �.�.).
// ������ ������� ������ ���������� �������� ������� EvalStr ��� ����������
// ���������: EvalStr(expr, &arg, 0, der, 0).
extern double EvalStr (char *, double, unsigned = 0);
//---------------------------------------------------------------------------
// ���������� ��������� (��������� ��������). ���������:
// 1) char *expr - ��������� �� ������, ���������� ���������;
// 2) double *args - ������ ���������� (������� ������� �������� x1,
//    ������ ������� - x2 � �.�);
// 3) unsigned arg_count - ���������� ���������� � ���������;
// 4) unsigned der - ������� ����������� (�� ��������� 0);
// 5) unsigned arg_idx - �� ������ ��������� ������� ����������� (0 - ��
//    ��������� - �� ������������� ���������� ���������, 1 - �� x1 ���
//    ���������� ���������, 2 - �� x2 � �.�.).
// ������ ������� ������� ��������� ��� pstr ������� ������� CreatePolStr,
// �����, ���� ���� ������, ���������� ����, ����� ���������� ��������
// ������� EvalPolStr(pstr, args, der, arg_idx). ���������: ���� ���� � ��
// �� ��������� ����������� ��������� ���, �� ��������� ������ ��� ���,
// ������������ ��� � ������������ ������ ����� ������������� �����������,
// ��� �� ���� ������. � ���� ������ ����� ���� ��� �������������� �������
// ��� � ������� ������� CreatePolStr, � ����� �������� EvalPolStr ������
// EvalStr.
extern double EvalStr (char *, double *, unsigned, unsigned = 0, unsigned = 0);
//---------------------------------------------------------------------------
// ���������� ��������� � ���� ��� (��������� ��������). ���������:
// 1) char *pstr - ��������� �� ������, ���������� ���;
// 2) double arg - �������� ���������;
// 3) unsigned der - ������� ����������� (�� ��������� 0).
// ������ ������� ������ ���������� �������� ������� EvalPolStr ���
// ���������� ���������: EvalPolStr(pstr, &arg, der, 0).
extern double EvalPolStr (char *, double, unsigned = 0);
//---------------------------------------------------------------------------
// ���������� ��������� � ���� ��� (��������� ��������). ��� �������� �������
// ��� ���������� ���������, ��� ��������� ������� ��� ��� ����� �������� ��.
// ���������:
// 1) char *pstr - ��������� �� ������, ���������� ���;
// 2) double *args - ������ ����������;
// 3) unsigned der - ������� ����������� (�� ��������� 0);
// 4) unsigned arg_idx - �� ������ ��������� ������� ����������� (��
//    ��������� 0).
// ������� ���������� �������� ���������, ���� �� ����� ���������� �� ����
// ������, ����� ����. ������ ERR_UNKNOWN_DER ��������� � ��� ������, ����
// ���������� ��������� ����������� ���������. ���� ��������� �������� ������
// �������� +, - � *, �� ����� �������� ����� ��� �����������. ���� ���
// �������� ������ ������� � ��������, �� ����� ��������� ������ ������ �
// ������ �����������.
extern double EvalPolStr (char *, double *, unsigned = 0, unsigned = 0);
//---------------------------------------------------------------------------
#endif
//---------------------------------------------------------------------------

