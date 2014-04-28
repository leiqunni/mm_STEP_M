#include "stdafx.h"
#include "STEPlugin.h"
#include "Vqf.h"

bool LoadAttributeFileVQF(FILE_INFO *pFileMP3);
bool WriteAttributeFileVQF(FILE_INFO *pFileMP3);

bool LoadAttributeFileVQF(FILE_INFO *pFileMP3)
{
    CVqf vqf;
    if(vqf.Load(GetFullPath(pFileMP3)) != ERROR_SUCCESS){
        return false;
    }
	DWORD dwSize;
	wchar_t *data;
	//タイトル
	data = vqf.GetField('N','A','M','E',&dwSize);
	if(data){
        SetTrackNameSI(pFileMP3, (const char*)data);
    }
	//アーティスト
	data = vqf.GetField('A','U','T','H',&dwSize);
	if(data){
		SetArtistNameSI(pFileMP3, (const char*)data);
	}
	//保存名
	//data = vqf.GetField('F','I','L','E',&dwSize);
	//if(data){
	//}
	//著作権
	data = vqf.GetField('(','c',')',' ',&dwSize);
	if(data){
		SetCopyrightSI(pFileMP3, (const char*)data);
	}
    //コメント
	data = vqf.GetField('C','O','M','T',&dwSize);
	if(data){
		SetCommentSI(pFileMP3, (const char*)data);
	}

	SetPlayTime(pFileMP3, vqf.GetTime());
	SetAudioFormat(pFileMP3, vqf.GetFormatString());

    return true;
}

bool WriteAttributeFileVQF(FILE_INFO *pFileMP3)
{
    CVqf vqf;
    if(vqf.Load(GetFullPath(pFileMP3)) != ERROR_SUCCESS){
        return false;
    }
    CString strTmp;
    //タイトル
	vqf.SetField('N','A','M','E',
                (const wchar_t *)(LPCSTR)GetTrackNameSI(pFileMP3),
                wcslen(GetTrackNameSI(pFileMP3)));
    //アーティスト
	vqf.SetField('A','U','T','H',
                (const wchar_t *)(LPCSTR)GetArtistNameSI(pFileMP3),
                wcslen(GetArtistNameSI(pFileMP3)));
    //保存名
	//vqf.SetField('F','I','L','E',
    //              ???,
    //              ???);
    //著作権
	vqf.SetField('(','c',')',' ',
		        (const wchar_t *)(LPCSTR)GetCopyrightSI(pFileMP3),
                  wcslen(GetCopyrightSI(pFileMP3)));
    //コメント
	vqf.SetField('C','O','M','T',
                (const wchar_t *)(LPCSTR)GetCommentSI(pFileMP3),
                wcslen(GetCommentSI(pFileMP3)));
    return vqf.Save(NULL, GetFullPath(pFileMP3)) == ERROR_SUCCESS;
}
