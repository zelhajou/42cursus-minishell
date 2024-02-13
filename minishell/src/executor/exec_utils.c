void		_standards_init(s_tree *head, int *_fd, int *_piped)
{
	_piped[2] = 1;
	//>
	if (is_red(head->val) || head->type)
		_piped[2] = 0;
	//>
	if (_piped[5] > 0)
		_piped[1] = 1;
	else if (!_piped[4])
		_piped[1] = 0;
}

void	_standards_out(s_tree *head, int *_fd, int *_piped)
{
	if (_piped[2] && !is_red(head->val))
		_piped[5] -= 1;
	if (_piped[1])
		_piped[0] = 1;
}

void	__pipes_count(s_tree *head, int *_piped)
{
	if (str_cmp(head->val, "|", NULL))
		_piped[5] += 1;
	if (head->right)
		__pipes_count(head->right, _piped);
	if (head->left)
		__pipes_count(head->left, _piped);
}

void	__in_redirection_count(s_tree *head, int *_piped)
{
	head->type = 0;
	if (str_cmp(head->val, "<", "<<"))
		_piped[3] += 1;
	if (head->right)
		__in_redirection_count(head->right, _piped);
	if (head->left)
		__in_redirection_count(head->left, _piped);
}

void	__out_redirection_count(s_tree *head, int *_piped)
{
	head->type = 0;
	if (str_cmp(head->val, ">", ">>"))
		_piped[4] += 1;
	if (head->right)
		__out_redirection_count(head->right, _piped);
	if (head->left)
		__out_redirection_count(head->left, _piped);
}
