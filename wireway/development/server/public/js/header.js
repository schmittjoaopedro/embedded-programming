$.get('/header', function(data) {
	$('body').prepend(data);
});