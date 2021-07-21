#pragma once

#include "d3dUtil.h"

class Camera;

class Ssao
{
public:
	Ssao(ID3D11Device* device, ID3D11DeviceContext* dc, int width, int height, float fovy, float farZ);
	~Ssao();

	ID3D11ShaderResourceView* NormalDepthSRV();
	ID3D11ShaderResourceView* AmbientSRV();

	void OnSize(int width, int height, float fovy, float farZ);
	void SetNormalDepthRenderTarget(ID3D11DepthStencilView* dsv);
	void ComputeSsao(const Camera& camera);
	void BlurAmbientMap(int blurCount);

private:
	Ssao(const Ssao& rhs);
	Ssao& operator=(const Ssao& rhs);

	void BlurAmbientMap(ID3D11ShaderResourceView* inputSRV, ID3D11RenderTargetView* outputRTV, bool horzBlur);

	void BuildFrustumFarCorners(float fovy, float farZ);

	void BuildFullScreenQuad();

	void BuildTextureViews();
	void ReleaseTextureViews();

	void BuildRandomVectorTexture();

	void BuildOffsetVectors();

	void DrawFullScreenQuad();

private:
	ID3D11Device* md3dDevice;
	ID3D11DeviceContext* mDC;

	ID3D11Buffer* mScreenQuadVB;
	ID3D11Buffer* mScreenQuadIB;

	ID3D11ShaderResourceView* mRandomVectorSRV;

	ID3D11RenderTargetView* mNormalDepthRTV;
	ID3D11ShaderResourceView* mNormalDepthSRV;

	ID3D11RenderTargetView* mAmbientRTV0;
	ID3D11ShaderResourceView* mAmbientSRV0;

	ID3D11RenderTargetView* mAmbientRTV1;
	ID3D11ShaderResourceView* mAmbientSRV1;

	UINT mRenderTargetWidth;
	UINT mRenderTargetHeight;

	XMFLOAT4 mFrustumFarCorner[4];

	XMFLOAT4 mOffsets[14];

	D3D11_VIEWPORT mAmbientMapViewport;
};