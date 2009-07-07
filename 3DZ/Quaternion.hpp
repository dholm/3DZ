/*
 *  Quaternion.hpp
 *  3DZ
 *
 *  Created by David Holm on 2009-07-07.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef TDZ_QUATERNION_HPP
#define TDZ_QUATERNION_HPP

namespace TDZ {

	template <std::size_t N, typename ComponentT> class Vector;
	template <std::size_t M, std::size_t N, typename ComponentT> class Matrix;

	template<typename ComponentT>
	class Quaternion {
	public:
		Quaternion(const ComponentT& w = ComponentT(0), const ComponentT& x = ComponentT(0), const ComponentT& y = ComponentT(0), const ComponentT& z = ComponentT(0)) :
			m_quaternion()
		{
			m_quaternion.a[0] = w;
			m_quaternion.a[1] = x;
			m_quaternion.a[2] = y;
			m_quaternion.a[3] = z;
		}

		Quaternion(const ComponentT& w, const Vector<3, ComponentT>& vec) :
			m_quaternion()
		{
			m_quaternion.a[0] = w;
			m_quaternion.a[1] = vec[0];
			m_quaternion.a[2] = vec[1];
			m_quaternion.a[3] = vec[2];
		}
		
		inline const ComponentT& operator[](std::size_t i) const {
			return m_quaternion.a[i];
		}
		
		inline ComponentT& operator[](std::size_t i) {
			return m_quaternion.a[i];
		}
		
		Quaternion<ComponentT> operator*(const Quaternion<ComponentT>& quaternion) const {
			Quaternion<ComponentT> result(
				m_quaternion.a[0] * quaternion[1] + m_quaternion.a[1] * quaternion[0] + m_quaternion.a[2] * quaternion[3] - m_quaternion.a[3] * quaternion[2],
				m_quaternion.a[0] * quaternion[2] - m_quaternion.a[1] * quaternion[3] + m_quaternion.a[2] * quaternion[0] + m_quaternion.a[3] * quaternion[1],
				m_quaternion.a[0] * quaternion[3] + m_quaternion.a[1] * quaternion[2] - m_quaternion.a[2] * quaternion[1] + m_quaternion.a[3] * quaternion[0],
				m_quaternion.a[0] * quaternion[0] - m_quaternion.a[1] * quaternion[1] - m_quaternion.a[2] * quaternion[2] - m_quaternion.a[3] * quaternion[2]
			);
			return result;
		}
		
		Matrix<4, 4, ComponentT> toMatrix() const {
			Matrix<4, 4, ComponentT> matrix;
			
			matrix(0, 0) = ComponentT(1) - ComponentT(2) * m_quaternion.a[2] * m_quaternion.a[2] - ComponentT(2) * m_quaternion.a[3] * m_quaternion.a[3];
			matrix(0, 1) = ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[2] + ComponentT(2) * m_quaternion.a[3] * m_quaternion.a[0];
			matrix(0, 2) = ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[3] - ComponentT(2) * m_quaternion.a[2] * m_quaternion.a[0];
			matrix(0, 3) = ComponentT(0);
			
			matrix(1, 0) = ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[2] - ComponentT(2) * m_quaternion.a[3] * m_quaternion.a[0];
			matrix(1, 1) = ComponentT(1) - ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[1] - ComponentT(2) * m_quaternion.a[3] * m_quaternion.a[3];
			matrix(1, 2) = ComponentT(2) * m_quaternion.a[3] * m_quaternion.a[2] + ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[0];
			matrix(1, 3) = ComponentT(0);
			
			matrix(2, 0) = ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[2] + ComponentT(2) * m_quaternion.a[2] * m_quaternion.a[0];
			matrix(2, 1) = ComponentT(2) * m_quaternion.a[3] * m_quaternion.a[2] - ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[0];
			matrix(2, 2) = ComponentT(1) - ComponentT(2) * m_quaternion.a[0] * m_quaternion.a[0] - ComponentT(2) * m_quaternion.a[1] * m_quaternion.a[1];
			matrix(2, 3) = ComponentT(0);
			
			matrix(3, 0) = ComponentT(0);
			matrix(3, 1) = ComponentT(0);
			matrix(3, 2) = ComponentT(0);
			matrix(3, 3) = ComponentT(1);
			
			return matrix;
		}
		
		friend Quaternion<ComponentT> conjugate(const Quaternion<ComponentT>& quaternion) {
			Quaternion<ComponentT> result(
				quaternion[0],
				-quaternion[1],
				-quaternion[2],
				-quaternion[3]
			);
			return result;
		}
		
		friend std::ostream& operator<<(std::ostream& outStream, const Quaternion<ComponentT>& quaternion) {
			outStream << "[";
			for (std::size_t i = 0; i < 4; ++i) {
				outStream << quaternion.m_quaternion.a[i];
				if (i < (4 - 1)) {
					outStream << ", ";
				}
			}
			outStream << "]";
			return outStream;
		}
		
	private:
		struct {
			ComponentT a[4] __attribute__ ((packed));
		} m_quaternion __attribute__ ((aligned (16)));
	};

	template <typename ComponentT>
	struct RotationQuaternion {
		static Quaternion<ComponentT> create(const ComponentT& radian, const Vector<3, ComponentT>& vector) {
			const ComponentT halfRadian(radian / 2);
			const ComponentT sinRadian(sin(halfRadian));
			
			return Quaternion<ComponentT>(
				cos(halfRadian),
				vector[0] * sinRadian,
				vector[1] * sinRadian,
				vector[2] * sinRadian
			);
		}
	};
	
} // TDZ

#endif /* TDZ_QUATERNION_HPP */
