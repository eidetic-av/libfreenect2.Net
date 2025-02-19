#pragma once

#include <libfreenect2.hpp>
#include "ManagedWrapper.h"

namespace libfreenect2Net
{
	public enum class FrameDataFormat
	{
		/// <summary>Invalid format.</summary>
		Invalid = 0,
		/// <summary>Raw bitstream. <see cref='Frame::BytesPerPixel'/> defines the total number of bytes.
		Raw = 1,
		/// <summary>A 4-byte float per pixel.</summary>
		Float = 2,
		/// <summary>4 bytes of B, G, R, and unused per pixel.</summary>
		Bgrx = 4,
		/// <summary>4 bytes of R, G, B, and unused per pixel.</summary>
		Rgbx = 5,
		/// <summary>1 byte of gray per pixel.</summary>
		Gray = 6,
	};


	public ref class Frame : public Internals::ManagedWrapper<libfreenect2::Frame>
	{
	private:
		initonly TimeSpan _timeStamp;
		Frame(libfreenect2::Frame* instance);
		static int GetBytesPerPixelForDataFormat(FrameDataFormat dataFormat);
		libfreenect2::Frame::Format ConvertDataFormat(FrameDataFormat value);

	internal:
		static explicit operator Frame^ (libfreenect2::Frame* instance);

	public:
		/// <summary>
		/// Creates a new instance of <see cref="Frame"/> with specified
		/// dimensions and data format.
		/// </summary>
		/// <param name="width">Frame width.</param>
		/// <param name="height">Frame height.</param>
		/// <param name="dataFormat">
		/// Frame's data format.
		/// <c>Raw</c> and <c>Invalid</c> are not allowed.
		/// </param>
		Frame(int width, int height, FrameDataFormat dataFormat);

		property int Width
		{
			int get() { return (int)Instance->width; }
		}

		property int Height
		{
			int get() { return (int)Instance->height; }
		}

		property FrameDataFormat DataFormat
		{
			FrameDataFormat get() { return (FrameDataFormat)Instance->format; }
		}

		property int BytesPerPixel
		{
			int get() { return (int)Instance->bytes_per_pixel; }
		}

		property IntPtr Data
		{
			IntPtr get() { return IntPtr(Instance->data); }
		}

		/// <summary>Gets data size in bytes.</summary>
		/// <remarks>
		/// Returns <c>-1</c> if the size is undefined (e.g. invalid format).
		/// </summary>
		property int DataSize
		{
			int get();
		}

		property TimeSpan TimeStamp
		{
			TimeSpan get() { return _timeStamp; }
		}

		/// <summary>Sequence number of the frame.</summary>
		/// <remarks>Simple increasing counter.</summary>
		property long long Sequence
		{
			long long get() { return (long)Instance->sequence; }
		}

		/// <summary>Exposure value for the frame.</summary>
		/// <remarks>Ranges from 0.5 (bright light) to ~60.0 (sensor covered).
		property float Exposure
		{
			float get() { return Instance->exposure; }
		}

		/// <summary>Gain value for the frame.</summary>
		/// <remarks>Ranges from 1.0 (bright light) to 1.5 (sensor covered).
		property float Gain
		{
			float get() { return Instance->gain; }
		}

		/// <summary>Gamma value for the frame.</summary>
		/// <remarks>Ranges from 1.0 (bright light) to 6.4 (sensor covered).
		property float Gamma
		{
			float get() { return Instance->gamma; }
		}

		/// <summary>Indicates whether the frame has an error.</summary>
		/// <remarks>Possible errors are not specified, as well as which properties they affect.</remarks>
		property bool HasError
		{
			bool get() { return Instance->status != 0; }
		}
	};
}