#pragma once
class CTileMap
{
public:
	CTileMap();

	~CTileMap();

	void TileMapDrawing();

private:

	BYTE mTileMap[dfMAP_HEIGHT][dfMAP_WIDTH];

	BYTE mTileAttribute[dfMAP_HEIGHT][dfMAP_WIDTH];

};

extern CTileMap tileMap;
