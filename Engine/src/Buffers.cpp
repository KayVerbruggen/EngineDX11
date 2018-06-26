#include "Buffers.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& indices)
{
	CD3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(CD3D11_BUFFER_DESC));

	bufferDesc.ByteWidth = (UINT)indices.size() * sizeof(unsigned int);
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	data.pSysMem = indices.data();
	auto hr = Renderer::GetDevice()->CreateBuffer(&bufferDesc, &data, &m_buffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create index buffer", "Direct3D 11 Error", MB_OK);
}

IndexBuffer::~IndexBuffer()
{
	if (m_buffer)
	{
		m_buffer->Release();
		m_buffer = 0;
	}
}

void IndexBuffer::Bind() const
{
	Renderer::GetDeviceContext()->IASetIndexBuffer(m_buffer, DXGI_FORMAT_R32_UINT, 0);
}

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices)
{
	CD3D11_BUFFER_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(CD3D11_BUFFER_DESC));

	bufferDesc.ByteWidth = (UINT)vertices.size() * sizeof(Vertex);
	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

	data.pSysMem = vertices.data();
	auto hr = Renderer::GetDevice()->CreateBuffer(&bufferDesc, &data, &m_buffer);
	if (hr != S_OK)
		MessageBox(0, "Failed to create vertex buffer", "Direct3D 11 Error", MB_OK);
}

VertexBuffer::~VertexBuffer()
{
	if (m_buffer)
	{
		m_buffer->Release();
		m_buffer = 0;
	}
}

void VertexBuffer::Bind() const
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_buffer, &stride, &offset);
}