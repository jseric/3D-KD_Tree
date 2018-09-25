
// This file is taken from DirectX tool Kit.
// See https://directxtk.codeplex.com/

//--------------------------------------------------------------------------------------
// File: VertexTypes.h
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//--------------------------------------------------------------------------------------

#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#else
#include <d3d11_1.h>
#endif

#include <DirectXMath.h>


namespace DirectX
{
#if (DIRECTX_MATH_VERSION < 305) && !defined(XM_CALLCONV)
#define XM_CALLCONV __fastcall
	typedef const XMVECTOR& HXMVECTOR;
	typedef const XMMATRIX& FXMMATRIX;
#endif

    // Vertex struct holding position information
    // Used for KD Trees
    struct VertexPosition
    {
        XMFLOAT3 position;

        VertexPosition(const float x = 0.0f, 
            const float y = 0.0f,
            const float z = 0.0f)
            : position{ XMFLOAT3{ x, y, z} }
        {
        }

        VertexPosition(XMFLOAT3 const& position)
            : position(position)
        { 
        }

        VertexPosition(XMFLOAT3&)
            : position(position)
        { 
        }

        VertexPosition(FXMVECTOR position)
        {
            XMStoreFloat3(&this->position, position);
        }

        float& operator[](unsigned int index)
        {
            switch (index % 8)
            {
            case 0:
                return position.x;
            case 1:
                return position.y;
            case 2:
                return position.z;

            default:
                return position.x;
            }
        }

        std::string ToString(void)
        {
            std::stringstream ss{};

            ss << "Position: ";
            ss << "[ " << position.x << " " << position.y;
            ss << " " << position.z << " ]" << std::endl;

            return ss.str();
        }

        void operator=(VertexPosition v)
        {
            position = v.position;
        }
    };

	// Vertex struct holding position and color information.
	struct VertexPositionColor
	{
		VertexPositionColor()
		{ }

		VertexPositionColor(XMFLOAT3 const& position, XMFLOAT4 const& color)
			: position(position),
			color(color)
		{ }

		VertexPositionColor(FXMVECTOR position, FXMVECTOR color)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat4(&this->color, color);
		}

		XMFLOAT3 position;
		XMFLOAT4 color;

		static const int InputElementCount = 2;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct holding position and texture mapping information.
	struct VertexPositionTexture
	{
		VertexPositionTexture()
		{ }

		VertexPositionTexture(XMFLOAT3 const& position, XMFLOAT2 const& textureCoordinate)
			: position(position),
			textureCoordinate(textureCoordinate)
		{ }

		VertexPositionTexture(FXMVECTOR position, FXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		XMFLOAT3 position;
		XMFLOAT2 textureCoordinate;

		static const int InputElementCount = 2;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct holding position and normal vector.
	struct VertexPositionNormal
	{
		VertexPositionNormal()
		{ }

		VertexPositionNormal(XMFLOAT3 const& position, XMFLOAT3 const& normal)
			: position(position),
			normal(normal)
		{ }

		VertexPositionNormal(FXMVECTOR position, FXMVECTOR normal)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
		}

		XMFLOAT3 position;
		XMFLOAT3 normal;

		static const int InputElementCount = 2;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct holding position, color, and texture mapping information.
	struct VertexPositionColorTexture
	{
		VertexPositionColorTexture()
		{ }

		VertexPositionColorTexture(XMFLOAT3 const& position, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
			: position(position),
			color(color),
			textureCoordinate(textureCoordinate)
		{ }

		VertexPositionColorTexture(FXMVECTOR position, FXMVECTOR color, FXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat4(&this->color, color);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT2 textureCoordinate;

		static const int InputElementCount = 3;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct holding position, normal vector, and color information.
	struct VertexPositionNormalColor
	{
		VertexPositionNormalColor()
		{ }

		VertexPositionNormalColor(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& color)
			: position(position),
			normal(normal),
			color(color)
		{ }

		VertexPositionNormalColor(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR color)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
			XMStoreFloat4(&this->color, color);
		}

		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT4 color;

		static const int InputElementCount = 3;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct holding position, normal vector, and texture mapping information.
	struct VertexPositionNormalTexture
	{
		VertexPositionNormalTexture()
		{ }

		VertexPositionNormalTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT2 const& textureCoordinate)
			: position(position),
			normal(normal),
			textureCoordinate(textureCoordinate)
		{ }

		VertexPositionNormalTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT2 textureCoordinate;

		static const int InputElementCount = 3;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct holding position, normal vector, color, and texture mapping information.
	struct VertexPositionNormalColorTexture
	{
		VertexPositionNormalColorTexture()
		{ }

		VertexPositionNormalColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
			: position(position),
			normal(normal),
			color(color),
			textureCoordinate(textureCoordinate)
		{ }

		VertexPositionNormalColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR color, CXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
			XMStoreFloat4(&this->color, color);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT4 color;
		XMFLOAT2 textureCoordinate;

		static const int InputElementCount = 4;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
	// tangent, color (RGBA), and texture mapping information
	struct VertexPositionNormalTangentColorTexture
	{
		VertexPositionNormalTangentColorTexture()
		{ }

		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT4 tangent;
		uint32_t color;
		XMFLOAT2 textureCoordinate;

		VertexPositionNormalTangentColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, uint32_t rgba, XMFLOAT2 const& textureCoordinate)
			: position(position),
			normal(normal),
			tangent(tangent),
			color(rgba),
			textureCoordinate(textureCoordinate)
		{
		}

		VertexPositionNormalTangentColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, uint32_t rgba, CXMVECTOR textureCoordinate)
			: color(rgba)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
			XMStoreFloat4(&this->tangent, tangent);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		VertexPositionNormalTangentColorTexture(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
			: position(position),
			normal(normal),
			tangent(tangent),
			textureCoordinate(textureCoordinate)
		{
			SetColor(color);
		}

		VertexPositionNormalTangentColorTexture(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, CXMVECTOR color, CXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
			XMStoreFloat4(&this->tangent, tangent);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);

			SetColor(color);
		}

		void __cdecl SetColor(XMFLOAT4 const& icolor) { SetColor(XMLoadFloat4(&icolor)); }
		void XM_CALLCONV SetColor(FXMVECTOR icolor);

		static const int InputElementCount = 5;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};


	// Vertex struct for Visual Studio Shader Designer (DGSL) holding position, normal,
	// tangent, color (RGBA), texture mapping information, and skinning weights
	struct VertexPositionNormalTangentColorTextureSkinning : public VertexPositionNormalTangentColorTexture
	{
		VertexPositionNormalTangentColorTextureSkinning()
		{ }

		uint32_t indices;
		uint32_t weights;

		VertexPositionNormalTangentColorTextureSkinning(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, uint32_t rgba,
			XMFLOAT2 const& textureCoordinate, XMUINT4 const& indices, XMFLOAT4 const& weights)
			: VertexPositionNormalTangentColorTexture(position, normal, tangent, rgba, textureCoordinate)
		{
			SetBlendIndices(indices);
			SetBlendWeights(weights);
		}

		VertexPositionNormalTangentColorTextureSkinning(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, uint32_t rgba, CXMVECTOR textureCoordinate,
			XMUINT4 const& indices, CXMVECTOR weights)
			: VertexPositionNormalTangentColorTexture(position, normal, tangent, rgba, textureCoordinate)
		{
			SetBlendIndices(indices);
			SetBlendWeights(weights);
		}

		VertexPositionNormalTangentColorTextureSkinning(XMFLOAT3 const& position, XMFLOAT3 const& normal, XMFLOAT4 const& tangent, XMFLOAT4 const& color,
			XMFLOAT2 const& textureCoordinate, XMUINT4 const& indices, XMFLOAT4 const& weights)
			: VertexPositionNormalTangentColorTexture(position, normal, tangent, color, textureCoordinate)
		{
			SetBlendIndices(indices);
			SetBlendWeights(weights);
		}

		VertexPositionNormalTangentColorTextureSkinning(FXMVECTOR position, FXMVECTOR normal, FXMVECTOR tangent, CXMVECTOR color, CXMVECTOR textureCoordinate,
			XMUINT4 const& indices, CXMVECTOR weights)
			: VertexPositionNormalTangentColorTexture(position, normal, tangent, color, textureCoordinate)
		{
			SetBlendIndices(indices);
			SetBlendWeights(weights);
		}

		void __cdecl SetBlendIndices(XMUINT4 const& iindices);

		void __cdecl SetBlendWeights(XMFLOAT4 const& iweights) { SetBlendWeights(XMLoadFloat4(&iweights)); }
		void XM_CALLCONV SetBlendWeights(FXMVECTOR iweights);

		static const int InputElementCount = 7;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};

	// Added by Vanity
	struct VertexPositionNormalTangentTexture
	{
		VertexPositionNormalTangentTexture() {}

		XMFLOAT3 position;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT2 textureCoordinate;

		VertexPositionNormalTangentTexture(XMFLOAT3 const& position,
			XMFLOAT3 const& normal,
			XMFLOAT3 const& tangent,
			XMFLOAT2 const& textureCoordinate)
			: position(position),
			normal(normal),
			tangent(tangent),
			textureCoordinate(textureCoordinate)
		{
		}

		VertexPositionNormalTangentTexture(FXMVECTOR position,
			FXMVECTOR normal,
			FXMVECTOR tangent,
			CXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat3(&this->normal, normal);
			XMStoreFloat3(&this->tangent, tangent);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		static const int InputElementCount = 4;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};
}
