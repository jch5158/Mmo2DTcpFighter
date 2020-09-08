#include "stdafx.h"
#include "CBaseObject.h"
#include "CPlayerObject.h"
#include "CScreenDib.h"
#include "CSpriteDib.h"
#include "CTileMap.h"

CTileMap tileMap;

CTileMap::CTileMap()
{

	memset(mTileAttribute, 0, dfMAP_HEIGHT * dfMAP_WIDTH);

	memset(mTileMap, 0, dfMAP_HEIGHT * dfMAP_WIDTH);
}

CTileMap::~CTileMap()
{

}

void CTileMap::TileMapDrawing()
{
	// 백 버퍼를 받는다.
	BYTE* pDestDib = ScreenDib.GetDibBuffer();
	
	// 백 버퍼의 가로길이
	int DestWidth = ScreenDib.GetWidth();

	// 백 버퍼의 세로길이
	int DestHeight = ScreenDib.GetHeight();

	//
	int cameraViewX = playerObj->m_iXpos - (dfRESOLUTION_WIDTH / 2);
	if (cameraViewX <= 0)
	{
		cameraViewX = 0;
	}
	else if(cameraViewX >= dfRANGE_MOVE_RIGHT - dfRESOLUTION_WIDTH)
	{
		cameraViewX = dfRANGE_MOVE_RIGHT - dfRESOLUTION_WIDTH;
	}


	int cameraViewY = playerObj->m_iYpos - ((dfRESOLUTION_HEIGHT / 2) + 50);
	if (cameraViewY <= 0)
	{
		cameraViewY = 0;
	}
	else if (cameraViewY >= dfRANGE_MOVE_BOTTOM - dfRESOLUTION_HEIGHT)
	{
		cameraViewY = dfRANGE_MOVE_BOTTOM - dfRESOLUTION_HEIGHT;
	}


	// 백 버퍼의 피치
	int pitch = ScreenDib.GetPitch();

	// 
	int tileX = cameraViewX / 64;
	int tileY = cameraViewY / 64;

	int remainderX = cameraViewX % 64;
	int remainderY = cameraViewY % 64;

	BYTE byTileIndex;

	for (int iCntY = 0; iCntY < 10; ++iCntY)
	{
		if (tileY + iCntY > 99)
		{
			break;
		}

		for (int iCntX = 0; iCntX < 12; ++iCntX)
		{
			if (tileX + iCntX > 99)
			{
				break;
			}
			//  90 + 9           88 + 11
			byTileIndex = mTileMap[tileY + iCntY][tileX + iCntX];

			SpriteDib.DrawImage(byTileIndex, (iCntX * 64) - remainderX, (iCntY * 64) - remainderY, pDestDib, DestWidth, DestHeight, pitch);

		}
	}

}
