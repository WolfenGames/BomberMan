#pragma once

class IPowerup
{
	public:
		virtual void	onUpdate()	= 0;
		virtual void	onRemove()	= 0;
		virtual void	onAdd() 	= 0;
};