extends Area2D

#se a variavel relacionada à gema for positiva o asset da gema some
func _process(_delta):
	if ScriptGlobal.gemaVermelha1:
		self.queue_free()
