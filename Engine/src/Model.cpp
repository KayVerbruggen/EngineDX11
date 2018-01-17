#include "Model.h"

Model::Model(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext)
{
	m_device = Device;
	m_deviceCon = DeviceContext;

	CreateVertexBuffer(m_vertices);
	CreateIndexBuffer(m_indices);
	CreateShaders("shaders\\BasicVS.cso", "shaders\\BasicPS.cso");
	CreateConstantBuffer();
	InitWorld();
	LoadTexture("res\\texture.png");
}

Model::~Model()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
	if (m_indexBuffer)
	{	
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}
	if (m_bufferPerObject)
	{
		m_bufferPerObject->Release();
		m_bufferPerObject = 0;
	}
}

void Model::Draw(Camera& cam)
{
	cam.SetWorld(localWorld);
	cbPerObj.wvp = XMMatrixTranspose(cam.GetWVP());
	m_deviceCon->UpdateSubresource(m_bufferPerObject, 0, nullptr, &cbPerObj, 0, 0);
	m_deviceCon->VSSetConstantBuffers(0, 1, &m_bufferPerObject);

	m_deviceCon->PSSetShaderResources(0, 1, &m_texture);
	m_deviceCon->PSSetSamplers(0, 1, &m_textureSamplerState);

	m_deviceCon->IASetInputLayout(m_inputLayout);
	m_deviceCon->VSSetShader(m_vertexShader, nullptr, 0);
	m_deviceCon->PSSetShader(m_pixelShader, nullptr, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	m_deviceCon->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	m_deviceCon->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceCon->DrawIndexed((UINT)m_indices.size(), 0, 0);
}

void Model::CreateShaders(const char* vsFileName, const char* psFileName)
{
	// Vertex shader creation
	std::ifstream vsFile(vsFileName, std::ios::binary);
	std::ifstream psFile(psFileName, std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	hr = m_device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	if (hr != S_OK)
		MessageBox(0, "Failed to create the vertex shader!", "D3D11 Error", MB_OK);

	hr = m_device->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);
	if (hr != S_OK)
		MessageBox(0, "Failed to create the pixel shader!", "D3D11 Error", MB_OK);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA }
	};

	hr = m_device->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
	if (hr != S_OK)
		MessageBox(0, "Failed to create input layout", "Direct3D 11 Error", MB_OK);
}

void Model::CreateVertexBuffer(const std::vector<Vertex>& vertices)
{
	CD3D11_BUFFER_DESC vertexBufferDesc;
	ZeroMemory(&vertexBufferDesc, sizeof(CD3D11_BUFFER_DESC));

	vertexBufferDesc.ByteWidth = (UINT)vertices.size() * sizeof(Vertex);
	vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.StructureByteStride = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(D3D11_SUBRESOURCE_DATA));

	vertexData.pSysMem = vertices.data();
	hr = m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create vertex buffer", "Direct3D 11 Error", MB_OK);
}

void Model::CreateIndexBuffer(const std::vector<unsigned int>& indices)
{
	CD3D11_BUFFER_DESC indexBufferDesc;
	ZeroMemory(&indexBufferDesc, sizeof(CD3D11_BUFFER_DESC));

	indexBufferDesc.ByteWidth = (UINT)indices.size() * sizeof(unsigned int);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.StructureByteStride = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	D3D11_SUBRESOURCE_DATA indexData;
	ZeroMemory(&indexData, sizeof(D3D11_SUBRESOURCE_DATA));

	indexData.pSysMem = indices.data();
	hr = m_device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create index buffer", "Direct3D 11 Error", MB_OK);
}

void Model::CreateConstantBuffer()
{
	CD3D11_BUFFER_DESC constantBufferDesc;
	ZeroMemory(&constantBufferDesc, sizeof(CD3D11_BUFFER_DESC));

	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(cbPerObject);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;

	hr = m_device->CreateBuffer(&constantBufferDesc, nullptr, &m_bufferPerObject);
	if (hr != S_OK)
		MessageBox(0, "Failed to create constant buffer", "Direct3D 11 Error", MB_OK);
}

void Model::InitWorld()
{
	localWorld = XMMatrixIdentity();

	XMVECTOR rotAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	rotation = XMMatrixRotationAxis(rotAxis, XMConvertToRadians(rotY));
	translation = XMMatrixTranslation(0.0f, 0.0f, 4.0f);

	//Set the model's world space using the transformations
	localWorld = translation * rotation;
}

void Model::LoadTexture(const char* texFile)
{
	hr = D3DX11CreateShaderResourceViewFromFile(m_device, texFile, nullptr, nullptr, &m_texture, nullptr);
	if (hr != S_OK)
	{
		MessageBox(0, "Failed to read texture from file", "D3DX11 Error", MB_OK);
		return;
	}

	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	hr = m_device->CreateSamplerState(&samplerDesc, &m_textureSamplerState);
	if (hr != S_OK)
		MessageBox(0, "Failed to create sampler state!", "Direct3D 11 Error", MB_OK);
}