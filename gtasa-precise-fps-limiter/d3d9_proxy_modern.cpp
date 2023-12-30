#include "pch.h"
#ifndef WIN8_1_AND_LOWER_COMPAT
#include "d3d9_proxy_modern.h"

HRESULT d3d9_device_proxy_modern::QueryInterface(REFIID riid, void** ppvObj)
{
	return m_pDirect3DDevice9.QueryInterface(riid, ppvObj);
}

ULONG d3d9_device_proxy_modern::AddRef(void)
{
	return m_pDirect3DDevice9.AddRef();
}

ULONG d3d9_device_proxy_modern::Release(void)
{
	return m_pDirect3DDevice9.Release();
}

HRESULT d3d9_device_proxy_modern::TestCooperativeLevel(void)
{
	return m_pDirect3DDevice9.TestCooperativeLevel();
}

UINT d3d9_device_proxy_modern::GetAvailableTextureMem(void)
{
	return m_pDirect3DDevice9.GetAvailableTextureMem();
}

HRESULT d3d9_device_proxy_modern::EvictManagedResources(void)
{
	return m_pDirect3DDevice9.EvictManagedResources();
}

HRESULT d3d9_device_proxy_modern::GetDirect3D(IDirect3D9** ppD3D9)
{
	return m_pDirect3DDevice9.GetDirect3D(ppD3D9);
}

HRESULT d3d9_device_proxy_modern::GetDeviceCaps(D3DCAPS9* pCaps)
{
	return m_pDirect3DDevice9.GetDeviceCaps(pCaps);
}

HRESULT d3d9_device_proxy_modern::GetDisplayMode(UINT iSwapChain, D3DDISPLAYMODE* pMode)
{
	return m_pDirect3DDevice9.GetDisplayMode(iSwapChain, pMode);
}

HRESULT d3d9_device_proxy_modern::GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS* pParameters)
{
	return m_pDirect3DDevice9.GetCreationParameters(pParameters);
}

HRESULT d3d9_device_proxy_modern::SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9* pCursorBitmap)
{
	return m_pDirect3DDevice9.SetCursorProperties(XHotSpot, YHotSpot, pCursorBitmap);
}

void d3d9_device_proxy_modern::SetCursorPosition(int X, int Y, DWORD Flags)
{
	return m_pDirect3DDevice9.SetCursorPosition(X, Y, Flags);
}

BOOL d3d9_device_proxy_modern::ShowCursor(BOOL bShow)
{
	return m_pDirect3DDevice9.ShowCursor(bShow);
}

HRESULT d3d9_device_proxy_modern::CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDirect3DDevice9.CreateAdditionalSwapChain(pPresentationParameters, pSwapChain);
}

HRESULT d3d9_device_proxy_modern::GetSwapChain(UINT iSwapChain, IDirect3DSwapChain9** pSwapChain)
{
	return m_pDirect3DDevice9.GetSwapChain(iSwapChain, pSwapChain);
}

UINT d3d9_device_proxy_modern::GetNumberOfSwapChains(void)
{
	return m_pDirect3DDevice9.GetNumberOfSwapChains();
}

HRESULT d3d9_device_proxy_modern::Reset(D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	return m_pDirect3DDevice9.Reset(pPresentationParameters);
}

HRESULT d3d9_device_proxy_modern::Present(CONST RECT* pSourceRect, CONST RECT* pDestRect, HWND hDestWindowOverride, CONST RGNDATA* pDirtyRegion)
{
	return m_pDirect3DDevice9.Present(pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}

HRESULT d3d9_device_proxy_modern::GetBackBuffer(UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface9** ppBackBuffer)
{
	return m_pDirect3DDevice9.GetBackBuffer(iSwapChain, iBackBuffer, Type, ppBackBuffer);
}

HRESULT d3d9_device_proxy_modern::GetRasterStatus(UINT iSwapChain, D3DRASTER_STATUS* pRasterStatus)
{
	return m_pDirect3DDevice9.GetRasterStatus(iSwapChain, pRasterStatus);
}

HRESULT d3d9_device_proxy_modern::SetDialogBoxMode(BOOL bEnableDialogs)
{
	return m_pDirect3DDevice9.SetDialogBoxMode(bEnableDialogs);
}

void d3d9_device_proxy_modern::SetGammaRamp(UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP* pRamp)
{
	return m_pDirect3DDevice9.SetGammaRamp(iSwapChain, Flags, pRamp);
}

void d3d9_device_proxy_modern::GetGammaRamp(UINT iSwapChain, D3DGAMMARAMP* pRamp)
{
	return m_pDirect3DDevice9.GetGammaRamp(iSwapChain, pRamp);
}

HRESULT d3d9_device_proxy_modern::CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateTexture(Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateVolumeTexture(Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateCubeTexture(EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateVertexBuffer(Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateIndexBuffer(Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Lockable, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateRenderTarget(Width, Height, Format, MultiSample, MultisampleQuality, Lockable, ppSurface, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality, BOOL Discard, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateDepthStencilSurface(Width, Height, Format, MultiSample, MultisampleQuality, Discard, ppSurface, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::UpdateSurface(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestinationSurface, CONST POINT* pDestPoint)
{
	return m_pDirect3DDevice9.UpdateSurface(pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint);
}

HRESULT d3d9_device_proxy_modern::UpdateTexture(IDirect3DBaseTexture9* pSourceTexture, IDirect3DBaseTexture9* pDestinationTexture)
{
	return m_pDirect3DDevice9.UpdateTexture(pSourceTexture, pDestinationTexture);
}

HRESULT d3d9_device_proxy_modern::GetRenderTargetData(IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	return m_pDirect3DDevice9.GetRenderTargetData(pRenderTarget, pDestSurface);
}

HRESULT d3d9_device_proxy_modern::GetFrontBufferData(UINT iSwapChain, IDirect3DSurface9* pDestSurface)
{
	return m_pDirect3DDevice9.GetFrontBufferData(iSwapChain, pDestSurface);
}

HRESULT d3d9_device_proxy_modern::StretchRect(IDirect3DSurface9* pSourceSurface, CONST RECT* pSourceRect, IDirect3DSurface9* pDestSurface, CONST RECT* pDestRect, D3DTEXTUREFILTERTYPE Filter)
{
	return m_pDirect3DDevice9.StretchRect(pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter);
}

HRESULT d3d9_device_proxy_modern::ColorFill(IDirect3DSurface9* pSurface, CONST RECT* pRect, D3DCOLOR color)
{
	return m_pDirect3DDevice9.ColorFill(pSurface, pRect, color);
}

HRESULT d3d9_device_proxy_modern::CreateOffscreenPlainSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool, IDirect3DSurface9** ppSurface, HANDLE* pSharedHandle)
{
	return m_pDirect3DDevice9.CreateOffscreenPlainSurface(Width, Height, Format, Pool, ppSurface, pSharedHandle);
}

HRESULT d3d9_device_proxy_modern::SetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9* pRenderTarget)
{
	return m_pDirect3DDevice9.SetRenderTarget(RenderTargetIndex, pRenderTarget);
}

HRESULT d3d9_device_proxy_modern::GetRenderTarget(DWORD RenderTargetIndex, IDirect3DSurface9** ppRenderTarget)
{
	return m_pDirect3DDevice9.GetRenderTarget(RenderTargetIndex, ppRenderTarget);
}

HRESULT d3d9_device_proxy_modern::SetDepthStencilSurface(IDirect3DSurface9* pNewZStencil)
{
	return m_pDirect3DDevice9.SetDepthStencilSurface(pNewZStencil);
}

HRESULT d3d9_device_proxy_modern::GetDepthStencilSurface(IDirect3DSurface9** ppZStencilSurface)
{
	return m_pDirect3DDevice9.GetDepthStencilSurface(ppZStencilSurface);
}

HRESULT d3d9_device_proxy_modern::BeginScene(void)
{
	return m_pDirect3DDevice9.BeginScene();
}

HRESULT d3d9_device_proxy_modern::EndScene(void)
{
	auto hr = m_pDirect3DDevice9.EndScene();
	if (frameLimiter.ShouldWait())
		frameLimiter.Wait();
	frameLimiter.SetFrameStart();
	return hr;
}

HRESULT d3d9_device_proxy_modern::Clear(DWORD Count, CONST D3DRECT* pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil)
{
	return m_pDirect3DDevice9.Clear(Count, pRects, Flags, Color, Z, Stencil);
}

HRESULT d3d9_device_proxy_modern::SetTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return m_pDirect3DDevice9.SetTransform(State, pMatrix);
}

HRESULT d3d9_device_proxy_modern::GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX* pMatrix)
{
	return m_pDirect3DDevice9.GetTransform(State, pMatrix);
}

HRESULT d3d9_device_proxy_modern::MultiplyTransform(D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX* pMatrix)
{
	return m_pDirect3DDevice9.MultiplyTransform(State, pMatrix);
}

HRESULT d3d9_device_proxy_modern::SetViewport(CONST D3DVIEWPORT9* pViewport)
{
	return m_pDirect3DDevice9.SetViewport(pViewport);
}

HRESULT d3d9_device_proxy_modern::GetViewport(D3DVIEWPORT9* pViewport)
{
	return m_pDirect3DDevice9.GetViewport(pViewport);
}

HRESULT d3d9_device_proxy_modern::SetMaterial(CONST D3DMATERIAL9* pMaterial)
{
	return m_pDirect3DDevice9.SetMaterial(pMaterial);
}

HRESULT d3d9_device_proxy_modern::GetMaterial(D3DMATERIAL9* pMaterial)
{
	return m_pDirect3DDevice9.GetMaterial(pMaterial);
}

HRESULT d3d9_device_proxy_modern::SetLight(DWORD Index, CONST D3DLIGHT9* pLight)
{
	return m_pDirect3DDevice9.SetLight(Index, pLight);
}

HRESULT d3d9_device_proxy_modern::GetLight(DWORD Index, D3DLIGHT9* pLight)
{
	return m_pDirect3DDevice9.GetLight(Index, pLight);
}

HRESULT d3d9_device_proxy_modern::LightEnable(DWORD Index, BOOL Enable)
{
	return m_pDirect3DDevice9.LightEnable(Index, Enable);
}

HRESULT d3d9_device_proxy_modern::GetLightEnable(DWORD Index, BOOL* pEnable)
{
	return m_pDirect3DDevice9.GetLightEnable(Index, pEnable);
}

HRESULT d3d9_device_proxy_modern::SetClipPlane(DWORD Index, CONST float* pPlane)
{
	return m_pDirect3DDevice9.SetClipPlane(Index, pPlane);
}

HRESULT d3d9_device_proxy_modern::GetClipPlane(DWORD Index, float* pPlane)
{
	return m_pDirect3DDevice9.GetClipPlane(Index, pPlane);
}

HRESULT d3d9_device_proxy_modern::SetRenderState(D3DRENDERSTATETYPE State, DWORD Value)
{
	return m_pDirect3DDevice9.SetRenderState(State, Value);
}

HRESULT d3d9_device_proxy_modern::GetRenderState(D3DRENDERSTATETYPE State, DWORD* pValue)
{
	return m_pDirect3DDevice9.GetRenderState(State, pValue);
}

HRESULT d3d9_device_proxy_modern::CreateStateBlock(D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9** ppSB)
{
	return m_pDirect3DDevice9.CreateStateBlock(Type, ppSB);
}

HRESULT d3d9_device_proxy_modern::BeginStateBlock(void)
{
	return m_pDirect3DDevice9.BeginStateBlock();
}

HRESULT d3d9_device_proxy_modern::EndStateBlock(IDirect3DStateBlock9** ppSB)
{
	return m_pDirect3DDevice9.EndStateBlock(ppSB);
}

HRESULT d3d9_device_proxy_modern::SetClipStatus(CONST D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDirect3DDevice9.SetClipStatus(pClipStatus);
}

HRESULT d3d9_device_proxy_modern::GetClipStatus(D3DCLIPSTATUS9* pClipStatus)
{
	return m_pDirect3DDevice9.GetClipStatus(pClipStatus);
}

HRESULT d3d9_device_proxy_modern::GetTexture(DWORD Stage, IDirect3DBaseTexture9** ppTexture)
{
	return m_pDirect3DDevice9.GetTexture(Stage, ppTexture);
}

HRESULT d3d9_device_proxy_modern::SetTexture(DWORD Stage, IDirect3DBaseTexture9* pTexture)
{
	return m_pDirect3DDevice9.SetTexture(Stage, pTexture);
}

HRESULT d3d9_device_proxy_modern::GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD* pValue)
{
	return m_pDirect3DDevice9.GetTextureStageState(Stage, Type, pValue);
}

HRESULT d3d9_device_proxy_modern::SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value)
{
	return m_pDirect3DDevice9.SetTextureStageState(Stage, Type, Value);
}

HRESULT d3d9_device_proxy_modern::GetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD* pValue)
{
	return m_pDirect3DDevice9.GetSamplerState(Sampler, Type, pValue);
}

HRESULT d3d9_device_proxy_modern::SetSamplerState(DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value)
{
	return m_pDirect3DDevice9.SetSamplerState(Sampler, Type, Value);
}

HRESULT d3d9_device_proxy_modern::ValidateDevice(DWORD* pNumPasses)
{
	return m_pDirect3DDevice9.ValidateDevice(pNumPasses);
}

HRESULT d3d9_device_proxy_modern::SetPaletteEntries(UINT PaletteNumber, CONST PALETTEENTRY* pEntries)
{
	return m_pDirect3DDevice9.SetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT d3d9_device_proxy_modern::GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY* pEntries)
{
	return m_pDirect3DDevice9.GetPaletteEntries(PaletteNumber, pEntries);
}

HRESULT d3d9_device_proxy_modern::SetCurrentTexturePalette(UINT PaletteNumber)
{
	return m_pDirect3DDevice9.SetCurrentTexturePalette(PaletteNumber);
}

HRESULT d3d9_device_proxy_modern::GetCurrentTexturePalette(UINT* PaletteNumber)
{
	return m_pDirect3DDevice9.GetCurrentTexturePalette(PaletteNumber);
}

HRESULT d3d9_device_proxy_modern::SetScissorRect(CONST RECT* pRect)
{
	return m_pDirect3DDevice9.SetScissorRect(pRect);
}

HRESULT d3d9_device_proxy_modern::GetScissorRect(RECT* pRect)
{
	return m_pDirect3DDevice9.GetScissorRect(pRect);
}

HRESULT d3d9_device_proxy_modern::SetSoftwareVertexProcessing(BOOL bSoftware)
{
	return m_pDirect3DDevice9.SetSoftwareVertexProcessing(bSoftware);
}

BOOL d3d9_device_proxy_modern::GetSoftwareVertexProcessing(void)
{
	return m_pDirect3DDevice9.GetSoftwareVertexProcessing();
}

HRESULT d3d9_device_proxy_modern::SetNPatchMode(float nSegments)
{
	return m_pDirect3DDevice9.SetNPatchMode(nSegments);
}

float d3d9_device_proxy_modern::GetNPatchMode(void)
{
	return m_pDirect3DDevice9.GetNPatchMode();
}

HRESULT d3d9_device_proxy_modern::DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount)
{
	return m_pDirect3DDevice9.DrawPrimitive(PrimitiveType, StartVertex, PrimitiveCount);
}

HRESULT d3d9_device_proxy_modern::DrawIndexedPrimitive(D3DPRIMITIVETYPE Type, INT BaseVertexIndex, UINT MinVertexIndex, UINT NumVertices, UINT startIndex, UINT primCount)
{
	return m_pDirect3DDevice9.DrawIndexedPrimitive(Type, BaseVertexIndex, MinVertexIndex, NumVertices, startIndex, primCount);
}

HRESULT d3d9_device_proxy_modern::DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDirect3DDevice9.DrawPrimitiveUP(PrimitiveType, PrimitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT d3d9_device_proxy_modern::DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertices, UINT PrimitiveCount, CONST void* pIndexData, D3DFORMAT IndexDataFormat, CONST void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
	return m_pDirect3DDevice9.DrawIndexedPrimitiveUP(PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount, pIndexData, IndexDataFormat, pVertexStreamZeroData, VertexStreamZeroStride);
}

HRESULT d3d9_device_proxy_modern::ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer9* pDestBuffer, IDirect3DVertexDeclaration9* pVertexDecl, DWORD Flags)
{
	return m_pDirect3DDevice9.ProcessVertices(SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags);
}

HRESULT d3d9_device_proxy_modern::CreateVertexDeclaration(CONST D3DVERTEXELEMENT9* pVertexElements, IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDirect3DDevice9.CreateVertexDeclaration(pVertexElements, ppDecl);
}

HRESULT d3d9_device_proxy_modern::SetVertexDeclaration(IDirect3DVertexDeclaration9* pDecl)
{
	return m_pDirect3DDevice9.SetVertexDeclaration(pDecl);
}

HRESULT d3d9_device_proxy_modern::GetVertexDeclaration(IDirect3DVertexDeclaration9** ppDecl)
{
	return m_pDirect3DDevice9.GetVertexDeclaration(ppDecl);
}

HRESULT d3d9_device_proxy_modern::SetFVF(DWORD FVF)
{
	return m_pDirect3DDevice9.SetFVF(FVF);
}

HRESULT d3d9_device_proxy_modern::GetFVF(DWORD* pFVF)
{
	return m_pDirect3DDevice9.GetFVF(pFVF);
}

HRESULT d3d9_device_proxy_modern::CreateVertexShader(CONST DWORD* pFunction, IDirect3DVertexShader9** ppShader)
{
	return m_pDirect3DDevice9.CreateVertexShader(pFunction, ppShader);
}

HRESULT d3d9_device_proxy_modern::SetVertexShader(IDirect3DVertexShader9* pShader)
{
	return m_pDirect3DDevice9.SetVertexShader(pShader);
}

HRESULT d3d9_device_proxy_modern::GetVertexShader(IDirect3DVertexShader9** ppShader)
{
	return m_pDirect3DDevice9.GetVertexShader(ppShader);
}

HRESULT d3d9_device_proxy_modern::SetVertexShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDirect3DDevice9.SetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT d3d9_device_proxy_modern::GetVertexShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDirect3DDevice9.GetVertexShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT d3d9_device_proxy_modern::SetVertexShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDirect3DDevice9.SetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT d3d9_device_proxy_modern::GetVertexShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDirect3DDevice9.GetVertexShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT d3d9_device_proxy_modern::SetVertexShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT  BoolCount)
{
	return m_pDirect3DDevice9.SetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT d3d9_device_proxy_modern::GetVertexShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDirect3DDevice9.GetVertexShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT d3d9_device_proxy_modern::SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9* pStreamData, UINT OffsetInBytes, UINT Stride)
{
	return m_pDirect3DDevice9.SetStreamSource(StreamNumber, pStreamData, OffsetInBytes, Stride);
}

HRESULT d3d9_device_proxy_modern::GetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer9** ppStreamData, UINT* pOffsetInBytes, UINT* pStride)
{
	return m_pDirect3DDevice9.GetStreamSource(StreamNumber, ppStreamData, pOffsetInBytes, pStride);
}

HRESULT d3d9_device_proxy_modern::SetStreamSourceFreq(UINT StreamNumber, UINT Setting)
{
	return m_pDirect3DDevice9.SetStreamSourceFreq(StreamNumber, Setting);
}

HRESULT d3d9_device_proxy_modern::GetStreamSourceFreq(UINT StreamNumber, UINT* pSetting)
{
	return m_pDirect3DDevice9.GetStreamSourceFreq(StreamNumber, pSetting);
}

HRESULT d3d9_device_proxy_modern::SetIndices(IDirect3DIndexBuffer9* pIndexData)
{
	return m_pDirect3DDevice9.SetIndices(pIndexData);
}

HRESULT d3d9_device_proxy_modern::GetIndices(IDirect3DIndexBuffer9** ppIndexData)
{
	return m_pDirect3DDevice9.GetIndices(ppIndexData);
}

HRESULT d3d9_device_proxy_modern::CreatePixelShader(CONST DWORD* pFunction, IDirect3DPixelShader9** ppShader)
{
	return m_pDirect3DDevice9.CreatePixelShader(pFunction, ppShader);
}

HRESULT d3d9_device_proxy_modern::SetPixelShader(IDirect3DPixelShader9* pShader)
{
	return m_pDirect3DDevice9.SetPixelShader(pShader);
}

HRESULT d3d9_device_proxy_modern::GetPixelShader(IDirect3DPixelShader9** ppShader)
{
	return m_pDirect3DDevice9.GetPixelShader(ppShader);
}

HRESULT d3d9_device_proxy_modern::SetPixelShaderConstantF(UINT StartRegister, CONST float* pConstantData, UINT Vector4fCount)
{
	return m_pDirect3DDevice9.SetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT d3d9_device_proxy_modern::GetPixelShaderConstantF(UINT StartRegister, float* pConstantData, UINT Vector4fCount)
{
	return m_pDirect3DDevice9.GetPixelShaderConstantF(StartRegister, pConstantData, Vector4fCount);
}

HRESULT d3d9_device_proxy_modern::SetPixelShaderConstantI(UINT StartRegister, CONST int* pConstantData, UINT Vector4iCount)
{
	return m_pDirect3DDevice9.SetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT d3d9_device_proxy_modern::GetPixelShaderConstantI(UINT StartRegister, int* pConstantData, UINT Vector4iCount)
{
	return m_pDirect3DDevice9.GetPixelShaderConstantI(StartRegister, pConstantData, Vector4iCount);
}

HRESULT d3d9_device_proxy_modern::SetPixelShaderConstantB(UINT StartRegister, CONST BOOL* pConstantData, UINT BoolCount)
{
	return m_pDirect3DDevice9.SetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}

HRESULT d3d9_device_proxy_modern::GetPixelShaderConstantB(UINT StartRegister, BOOL* pConstantData, UINT BoolCount)
{
	return m_pDirect3DDevice9.GetPixelShaderConstantB(StartRegister, pConstantData, BoolCount);
}
HRESULT d3d9_device_proxy_modern::DrawRectPatch(UINT Handle, CONST float* pNumSegs, CONST D3DRECTPATCH_INFO* pRectPatchInfo)
{
	return m_pDirect3DDevice9.DrawRectPatch(Handle, pNumSegs, pRectPatchInfo);
}

HRESULT d3d9_device_proxy_modern::DrawTriPatch(UINT Handle, CONST float* pNumSegs, CONST D3DTRIPATCH_INFO* pTriPatchInfo)
{
	return m_pDirect3DDevice9.DrawTriPatch(Handle, pNumSegs, pTriPatchInfo);
}

HRESULT d3d9_device_proxy_modern::DeletePatch(UINT Handle)
{
	return m_pDirect3DDevice9.DeletePatch(Handle);
}

HRESULT d3d9_device_proxy_modern::CreateQuery(D3DQUERYTYPE Type, IDirect3DQuery9** ppQuery)
{
	return m_pDirect3DDevice9.CreateQuery(Type, ppQuery);
}

void d3d9_device_proxy_modern::UpdateFrameLimit(s64 targetFramerate)
{
	frameLimiter.UpdateFramerateLimit(targetFramerate);
}
#endif
