����γo�Ӥ�k�H
�b�{�����A�`�`�Q�n�Ϊ�����T�ҥH�`�`�سy�@��h�ɨ�include
�ӥB�S�Q�n�i�H�b�ɮת�resouce�[�Jversion��T
(�ĪG���ͦbexe�ɫ��k��A�ݤ��e�A�̭���������T)
���O�o��resouce����T�����ק�A�S�`�`�ѰO�A�ҥH�N���o�Ӥ�k�X�{
�٦��N�O�i�H��TortoiseSVN�����������X


�ؼ�:
�۰ʲ��ͪ�����T
�ӳo�Ӫ�����T�|�۰ʭק�resource�ɪ�version�Ϭq
�٦�����version.h�A�o�̭��]�t�{���һݭn��������T


��k:

�@�B
�@���ɮ�:
Version_Create.bat  ==> ����Version.h
Version_ReadMe.txt  ==> ����

�p���ɮ�:
Version_Resource.rc2 ==> �Q��l�귽�ɥ]�t(�Y��Version.h�Mresource����Ƨ���m���@�ˡA�h�ݭn�ק鷺�e��Version.h���|)
Version_PreBuildEvent.bat ==> ��vs2005 vc6Ĳ�o�ΨϥΪ̦ۦ�Ĳ�o�Ӳ��ͪ����سy�A�D�n�]�wVersion_Create.bat�����|
Version_Set.bat  ==>  �ѨϥΪ̦ۤw�]�w�����M���~��T
Version.h  ==>  �۰ʲ��͡B��s�A�ϥΪ̤���ۦ�ק�

�G�B
�b�n�[�J������T��resource�ɡA�ק�p�U
============================================================
============================================================
============================================================
3 TEXTINCLUDE 
BEGIN
    "\r\n"
    "#include ""Version_Resource.rc2""  // non-Microsoft Visual C++ edited resources\r\n"
    "\0"
END


#ifndef APSTUDIO_INVOKED
/////////////////////////////////////////////////////////////////////////////
//
// Generated from the TEXTINCLUDE 3 resource.
//

#include "Version_Resource.rc2"  // non-Microsoft Visual C++ edited resources

/////////////////////////////////////////////////////////////////////////////
#endif    // not APSTUDIO_INVOKED

============================================================
============================================================
============================================================
���󦳤W���o�ӪF��H  
�]���Y�O�b��l��resource�ɭק�F�誺��
���U���Y�νs��ק�F��s�ɪ��ܡA�ڭ̩ҭק諸�F��N�|����
�ΤW���o�Ӥ�k�A�N�i�H�קK

�T�B
1.�Y�Ovs2005���s�边�b�]�w��pre-build event��command line�[�JVersion_PreBuildEvent.bat
2.�Y�Ovc6�b�n��ʰ���Version_PreBuildEvent.bat�A
�άO�ϥΫD�зǪ����k�b�]�w��pre-link step�[�JVersion_PreBuildEvent.bat

�|�B
�ק�Version_Set.bat�����U����T
�Y�n��svn�������i�H�[�J�A�h�]�wSET UseSvnRevVersion=1
�`�N:�ݭn��TortoiseSVN�A�٦��{�b����Ƨ��O��TortoiseSVN��checkout�X�Ӫ�

���u

���B
Version_PreBuildEvent.bat���ѼƸѻ�

set Version_H_PATH=Version.h  ==> Version.h�ɮת���}�A���i��b�O���ؿ��A�p..\Version.h
set Version_Set_PATH=Version_Set.bat ==> Version_Set.bath�ɮת���}�A���i��b�O���ؿ��A�p..\Version_Set.bat
set Version_Create_PATH=Version_Create.bat ==> Version_Create.bat�ɮת���}�A���i��b�O���ؿ��A�p..\Version_Create.bat
SET APP_SubWCRev=d:\Program Files\TortoiseSVN\bin\SubWCRev.exe ==> SubWCRev.exe�o���ɮת���}�A�ݭn�w��TortoiseSVN
set Svn_WorkingCopyPath=. ==> svn��WorkingCopyPath�A�ΨӨ��o�o�ӥؿ���revision�A�� . ��ܲ{�b���ؿ�


Omar (ID:badpp)
�U�� 08:11 2007/6/26



