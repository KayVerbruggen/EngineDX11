#pragma once

#include <d3d11.h>
#include <string>

#include "Light.h"
#include "Util.h"

class Shader
{
public:
	Shader(std::string vsFileName, std::string psFileName);
	~Shader();

	void Bind() const;
	
	inline void SetProjection(const XMMATRIX &proj) { m_cbObject.projection = XMMatrixTranspose(proj); };
	inline void SetView(const XMMATRIX &view) { m_cbObject.view = XMMatrixTranspose(view); };
	inline void SetWorld(const XMMATRIX &world) { m_cbObject.world = XMMatrixTranspose(world); };
	inline void SetBufferObject(const CBPerObject &cbObj) { m_cbObject = cbObj; };

	inline void SetLight(Light light) { m_cbFrame.light = light; };

private:
	ID3D11InputLayout* m_inputLayout;
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;

	ID3D11Buffer* m_bufferPerObject;
	CBPerObject m_cbObject;
	ID3D11Buffer* m_bufferPerFrame;
	CBPerFrame m_cbFrame;
};

