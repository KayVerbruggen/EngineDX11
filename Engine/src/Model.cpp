#include "Model.h"

Model::Model(ID3D11Device*& Device, ID3D11DeviceContext*& DeviceContext)
{
	m_device = Device;
	m_deviceCon = DeviceContext;

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
	auto hr = m_device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create vertex buffer", "Direct3D 11", MB_OK);

	// TODO: Make the index buffer work.
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
		MessageBox(0, "Failed to create index buffer", "Direct3D 11", MB_OK);

	// Vertex shader creation
	std::ifstream vsFile("shaders\\BasicVS.cso", std::ios::binary);
	std::ifstream psFile("shaders\\BasicPS.cso", std::ios::binary);

	std::vector<char> vsData = { std::istreambuf_iterator<char>(vsFile), std::istreambuf_iterator<char>() };
	std::vector<char> psData = { std::istreambuf_iterator<char>(psFile), std::istreambuf_iterator<char>() };

	m_device->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	m_device->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA}, 
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA }
	};

	m_device->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}

Model::~Model()
{
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = nullptr;
	}
	if (m_indexBuffer)
	{	
		m_indexBuffer->Release();
		m_indexBuffer = nullptr;
	}
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = nullptr;
	}
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = nullptr;
	}
}

void Model::Draw()
{
	m_deviceCon->IASetInputLayout(m_inputLayout);
	m_deviceCon->VSSetShader(m_vertexShader, nullptr, 0);
	m_deviceCon->PSSetShader(m_pixelShader, nullptr, 0);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	m_deviceCon->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	m_deviceCon->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	m_deviceCon->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_deviceCon->DrawIndexed((UINT)indices.size(), 0, 0);
}