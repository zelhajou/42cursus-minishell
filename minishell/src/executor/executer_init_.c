void	open_next_output(s_tree *head, int _out_index, int *_piped, int *_fd)
{
	if (_piped[4] && head->left
			&& str_cmp(head->val, ">", ">>"))
	{
		if (_piped[6] == _out_index)
		{
			if (str_cmp(head->val, ">>", NULL))
				_fd[1] = open(head->left->val, O_WRONLY| O_CREAT| O_APPEND, 0666);
			else
				_fd[1] = open(head->left->val, O_WRONLY| O_CREAT| O_TRUNC, 0666);
			_piped[1] = 1;
			//printf("--- got output file -> %s\n", head->left->val);
		}
		_piped[6] += 1;
	}
	if (_piped[4] && head->right)
		open_next_output(head->right, _out_index, _piped, _fd);
	if (_piped[4] && head->left)
		open_next_output(head->left, _out_index, _piped, _fd);
}

void	open_next_input(s_tree *head, int _in_index, int *_piped, int *_fd)
{
	if (_piped[3] && ((head->right && !is_red(head->right->val)) 
				|| head->left)
			&& str_cmp(head->val, "<", "<<"))
	{
		if (_piped[6] == _in_index)
		{
			if (head->right && head->right->type)
				_fd[0] = open(head->right->val, O_RDONLY);
			else
				_fd[0] = open(head->left->val, O_RDONLY);
			_piped[0] = 1;
			/*printf("--- got input file -> %s\n", (head->right && head->right->type)
			 * ? head->right->val : head->left->val);*/
		}
		_piped[6] += 1;
	}
	if (_piped[3] && head->right)
		open_next_input(head->right, _in_index, _piped, _fd);
	if (_piped[3] && head->left)
		open_next_input(head->left, _in_index, _piped, _fd);
}

void	__adapt_nodes_types(s_tree *head)
{
	if (is_red(head->val))
	{
		if (str_cmp(head->val, ">", ">>") && head->left)
			head->left->type = 1;
		else if (str_cmp(head->val, "<", "<<"))
		{
			if (head->right && !is_red(head->right->val))
				head->right->type = 1;
			else if (head->left)
				head->left->type = 1;
		}
		head->type = 0;
	}
	if (head->right)
		__adapt_nodes_types(head->right);
	if (head->left)
		__adapt_nodes_types(head->left);
}
